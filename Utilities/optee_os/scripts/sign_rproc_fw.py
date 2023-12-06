#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (C) 2020, STMicroelectronics - All Rights Reserved
#

try:
    from elftools.elf.elffile import ELFFile
    from elftools.elf.sections import SymbolTableSection
    from elftools.elf.enums import ENUM_P_TYPE_ARM
    from elftools.elf.enums import *
except ImportError:
    print("""
***
ERROR: "pyelftools" python module is not installed or version < 0.25.
***
""")
    raise

try:
    from Cryptodome.Hash import SHA256
    from Cryptodome.Signature import pkcs1_15
    from Cryptodome.PublicKey import RSA
    from Cryptodome.Signature import DSS
    from Cryptodome.PublicKey import ECC
except ImportError:
    print("""
***
ERROR: "pycryptodomex" python module should be installed.
***
""")
    raise

import os
import sys
import struct
import logging
import binascii

#  Generated file structure:
#
#                    ----+-------------+
#                   /    |    Magic    |
#                  /     +-------------+
#                 /      +-------------+
#                /       |   version   |
#               /        +-------------+
#              /         +-------------+
# +-----------+          | sign size   |   size of the signature
# |   Header  |          +-------------+   (in bytes, 64-bit aligned)
# +-----------+          +-------------+
#              \         | images size |   size of the images to load
#               \        +-------------+   (in bytes, 64-bit aligned)
#                \       +-------------+
#                 \      |  TLV size   |   Generic TLV size
#                  \     +-------------+   (in bytes, 64-bit aligned)
#                   \    +-------------+
#                    \   | PLAT TLV sz |   Platform TLV size
#                     \--+-------------+   (in bytes, 64-bit aligned)
#
#                        +-------------+   Signature of the header, the trailer
#                        | Signature   |   and optionally the firmware image if
#                        +-------------+   a hash table is not stored.
#
#                        +-------------+
#                        |   Firmware  |
#                        |    image 1  |
#                        +-------------+
#                               ...
#                        +-------------+
#                        |   Firmware  |
#                        |    image n  |
#                        +-------------+
#                  ------+-------------+
#                 /      |+-----------+|
#                /       ||   TLV     ||   Information used to authenticate the
#  +-----------+/        ||           ||   firmware, stored in
#  |  Trailer  |         |+-----------+|   Type-Length-Value format.
#  +-----------+\        |+-----------+|
#                \       || Platform  ||   Specific platform information,
#                 \      ||   TLV     ||   stored in Type-Length-Value format.
#                  \     |+-----------+|
#                   -----+-------------+
#
#  TLV and platform TLV chunk:
#
#                  -----+-------------+
#                 |     |    Magic    |
#     +-----------+     +-------------+
#     |   Header  |     +-------------+
#     +-----------+     |    size     |  size of the TLV payload
#                 |-----+-------------+
#                       +-------------+
#                       |     TLV     |  TLV structures
#                       |   payload   |
#                       +-------------+


TLV_VALUES = {
        'SIGNTYPE': 0x01,    # algorithm used for signature
        'HASHTYPE': 0x02,    # algorithm used for computing segment's hash
        'NUM_IMG': 0x03,     # number of images to load
        'IMGTYPE': 0x04,     # type of images to load
        'IMGSIZE': 0x05,     # size of an image to load
        'HASHTABLE': 0x10,   # segment hash table for authentication
        'PKEYINFO': 0x11,    # optional information to retrieve signature key
}

PLAT_TLV_PREDEF_VALUES = {
        'SBOOTADDR': 0x21,   # boot address of the secure firmware
        'NSBOOTADDR': 0x22,  # boot address of the non-secure firmware
}

TLV_INFO_MAGIC = 0x6907
PLAT_TLV_INFO_MAGIC = 0x6908
TLV_INFO_SIZE = 8

logging.basicConfig(stream=sys.stderr, level=logging.INFO)

ENUM_HASH_TYPE = dict(
    SHA256=1,
)

ENUM_SIGNATURE_TYPE = dict(
    RSA=1,
    ECC=2,
)

ENUM_BINARY_TYPE = dict(
    ELF=1,
)


def dump_buffer(buf, step=16, name="", logger=logging.info, indent=""):
    logger("%s%s:" % (indent, name))
    for i in range(0, len(buf), step):
        logger("%s    " % (indent) + " ".
               join(["%02X" % c for c in buf[i:i+step]]))
    logger("\n")


class TLV():
    def __init__(self, magic):
        self.magic = magic
        self.buf = bytearray()

    def __len__(self):
        return TLV_INFO_SIZE + len(self.buf)

    def add(self, kind, payload):
        """
        Add a TLV record.  Kind should be a string found in TLV_VALUES above.
        """
        if isinstance(kind, int):
            buf = struct.pack('BBH', kind, 0, len(payload))
        else:
            buf = struct.pack('BBH', TLV_VALUES[kind], 0, len(payload))

        # Ensure that each tlv is 64-bit aligned
        align_64b = (len(payload) + len(buf)) % 8
        self.buf += buf
        self.buf += payload
        if align_64b:
            self.buf += bytearray(8 - align_64b)

    def get(self):
        """
        Get a byte-array that concatenates all the TLV added with a TLV header.
        """
        if len(self.buf) == 0:
            return bytes()
        header = struct.pack('II', self.magic, len(self.buf))
        return header + bytes(self.buf)


class RSA_Signature(object):

    def __init__(self, key):
        self._hasher = SHA256.new()
        self.signer = pkcs1_15.new(key)

    def hash_compute(self, segment):
        self._hasher.update(segment)

    def sign(self):
        return self.signer.sign(self._hasher)


class ECC_Signature(object):

    def __init__(self, key):
        self._hasher = SHA256.new()
        self.signer = DSS.new(key, 'fips-186-3')

    def hash_compute(self, segment):
        self._hasher.update(segment)

    def sign(self):
        return self.signer.sign(self._hasher)


Signature = {
        1: RSA_Signature,
        2: ECC_Signature,
}


class SegmentHashStruct:
    pass


class SegmentHash(object):
    '''
        Hash table based on Elf program segments
    '''
    def __init__(self, img):
        self._num_segments = img.num_segments()
        self._pack_fmt = '<%dL' % 8
        self.img = img
        self.hashProgTable = bytes()
        self._offset = 0

    def get_table(self):
        '''
            Create a segment hash table containing for each segment:
                - the segments header
                - a hash of the segment
        '''
        h = SHA256.new()
        seg = SegmentHashStruct()
        self.size = (h.digest_size + 32) * self._num_segments
        logging.debug("hash section size %d" % self.size)
        del h
        self.buf = bytearray(self.size)
        self._bufview_ = memoryview(self.buf)

        for i in range(self._num_segments):
            h = SHA256.new()
            segment = self.img.get_segment(i)
            seg.header = self.img.get_segment(i).header
            logging.debug("compute hash for segment offset %s" % seg.header)
            h.update(segment.data())
            seg.hash = h.digest()
            logging.debug("hash computed: %s" % seg.hash)
            del h
            struct.pack_into('<I', self._bufview_, self._offset,
                             ENUM_P_TYPE_ARM[seg.header.p_type])
            self._offset += 4
            struct.pack_into('<7I', self._bufview_, self._offset,
                             seg.header.p_offset, seg.header.p_vaddr,
                             seg.header.p_paddr, seg.header.p_filesz,
                             seg.header.p_memsz, seg.header.p_flags,
                             seg.header.p_align)
            self._offset += 28
            struct.pack_into('<32B', self._bufview_, self._offset, *seg.hash)
            self._offset += 32
        dump_buffer(self.buf, name='hash table', indent="\t")
        return self.buf


class ImageHeader(object):
    '''
        Image header
    '''

    magic = 'HELF'   # SHDR_MAGIC
    version = 1

    MAGIC_OFFSET = 0
    VERSION_OFFSET = 4
    SIGN_LEN_OFFSET = 8
    IMG_LEN_OFFSET = 12
    TLV_LEN_OFFSET = 16
    PTLV_LEN_OFFSET = 20

    def __init__(self):
        self.size = 56

        self.magic = 0x3543A468
        self.version = 1
        self.sign_length = 0
        self.img_length = 0
        self.tlv_length = 0
        self.plat_tlv_len = 0

        self.shdr = struct.pack('<IIIIII',
                                self.magic, self.version,
                                self.sign_length, self.img_length,
                                self.tlv_length, self.plat_tlv_len)

    def dump(self):
        logging.info("\tMAGIC\t\t= %08X" % (self.magic))
        logging.info("\tHEADER_VERSION\t= %08X" % (self.version))
        logging.info("\tSIGN_LENGTH\t= %08X" % (self.sign_length))
        logging.info("\tIMAGE_LENGTH\t= %08X" % (self.img_length))
        logging.info("\tTLV_LENGTH\t= %08X" % (self.tlv_length))
        logging.info("\tPLAT_TLV_LENGTH\t= %08X" % (self.plat_tlv_len))

    def get_packed(self):
        return struct.pack('<IIIIII',
                           self.magic, self.version, self.sign_length,
                           self.img_length, self.tlv_length, self.plat_tlv_len)


def get_args(logger):
    from argparse import ArgumentParser, RawDescriptionHelpFormatter
    import textwrap
    command_base = ['sign']
    command_choices = command_base
    default_key = os.path.abspath(os.path.dirname(__file__)) + \
        '/../keys/default_rproc.pem'

    parser = ArgumentParser(
        description='Sign a remote processor firmware loadable by OP-TEE.',
        usage='\n   %(prog)s command [ arguments ]\n\n'

        '   command:\n' +
        '     sign      Generate signed loadable binary \n' +
        '                 Takes arguments --in, --out --key\n' +
        '   %(prog)s --help  show available commands and arguments\n\n',
        formatter_class=RawDescriptionHelpFormatter,
        epilog=textwrap.dedent(
            '''If no key is specified, the script will default try to ''' +
            '''use the following private key:''') + '\n' + default_key
        )
    parser.add_argument(
        'command', choices=command_choices, nargs='?',
        default='sign',
        help='Command, one of [' + ', '.join(command_base) + ']')
    parser.add_argument('--key', required=False,
                        help='Name of signing key file',
                        default=default_key,
                        dest='keyf')
    parser.add_argument('--key_info', required=False,
                        help='Name file containing extra key information',
                        dest='key_infof')
    parser.add_argument('--key_type', required=False,
                        help='Type of signing key: should be RSA or ECC',
                        default='RSA',
                        dest='key_type')
    parser.add_argument('--plat-tlv', required=False, nargs=2,
                        metavar=("ID", "value"), action='append',
                        help='platform TLV that will be placed into image '
                             'plat_tlv area. Add "0x" prefix to interpret '
                             'the value as an integer, otherwise it will be '
                             'interpreted as a string. Option can be used '
                             'multiple times to add multiple TLVs.',
                        default=[], dest='plat_tlv')
    parser.add_argument(
        '--in', required=True, dest='inf',
        help='Name of firmware input file', action='append')
    parser.add_argument(
        '--out', required=False, dest='outf',
        help='Name of the signed firmware output file,' +
             ' default rproc_fw.sig')

    parsed = parser.parse_args()

    # Set defaults for optional arguments.

    if parsed.outf is None:
        parsed.outf = str(parsed.inf)+'.sig'

    return parsed


def rsa_key(keyf):
    return RSA.importKey(open(keyf).read())


def ecc_key(keyf):
    return ECC.import_key(open(keyf).read())


key_type = {
        1: rsa_key,
        2: ecc_key,
}


def rsa_sig_size(key):
    return key.size_in_bytes()


def ecc_sig_size(key):
    # to be improve...
    # DSA size is N/4  so 64 for DSA (L,N) = (2048, 256)
    return 64


sig_size_type = {
        1: rsa_sig_size,
        2: ecc_sig_size,
}


class custom_tlv(object):
    '''
        custom tlv provided as argument
    '''

    def __init__(self):
        self.tlvs = {}
        self.custom_tlvs = TLV(PLAT_TLV_INFO_MAGIC)
        self.tlv_buff = bytearray()

    def generate_tlv(self, cust_tlv):
        # Get list of custom protected TLVs from the command-line
        for tlv in cust_tlv:
            if tlv[0].isalpha():
                if tlv[0] in PLAT_TLV_PREDEF_VALUES.keys():
                    tag = PLAT_TLV_PREDEF_VALUES[tlv[0]]
                    logging.debug("\ttag found \t= %s" % tag)
                else:
                    raise Exception(
                        'Predefined platform TLV %s not found' % tlv[0])
            else:
                tag = int(tlv[0], 0)

                if tag in PLAT_TLV_PREDEF_VALUES.values():
                    raise Exception(
                        'TLV %s conflicts with predefined platform TLV.'
                        % hex(tag))
            if tag in self.tlvs:
                raise Exception('Custom TLV %s already exists.' % hex(tag))

            value = tlv[1]
            if value.startswith('0x'):
                int_val = int(value[2:], 16)
                self.tlvs[tag] = int_val.to_bytes(4, 'little')
            else:
                self.tlvs[tag] = value.encode('utf-8')

        if self.tlvs is not None:
            for tag, value in self.tlvs.items():
                self.custom_tlvs.add(tag, value)
        self.tlv_buff = self.custom_tlvs.get()
        dump_buffer(self.tlv_buff, name='PROC_TLV', indent="\t")


def main():
    from Cryptodome.Signature import pss
    from Cryptodome.Hash import SHA256
    from Cryptodome.PublicKey import RSA
    import base64
    import logging
    import struct

    logging.basicConfig()
    logger = logging.getLogger(os.path.basename(__file__))

    args = get_args(logger)

    # Initialise the header */
    s_header = ImageHeader()
    tlv = TLV(TLV_INFO_MAGIC)

    sign_type = ENUM_SIGNATURE_TYPE[args.key_type]
    get_key = key_type.get(sign_type, lambda: "Invalid sign type")

    key = get_key(args.keyf)

    if not key.has_private():
        logger.error('Provided key cannot be used for signing, ' +
                     'please use offline-signing mode.')
        sys.exit(1)

    tlv.add('SIGNTYPE', sign_type.to_bytes(1, 'little'))

    images_type = []
    hash_tlv = bytearray()
    images_size = []

    # Firmware image
    for inputf in args.inf:
        logging.debug("image  %s" % inputf)
        input_file = open(inputf, 'rb')
        img = ELFFile(input_file)

        # Only ARM machine has been tested and well supported yet.
        # Indeed this script uses of ENUM_P_TYPE_ARM dic
        assert img.get_machine_arch() in ["ARM"]

        # Need to reopen the file to get the raw data
        with open(inputf, 'rb') as f:
            bin_img = f.read()
        size = len(bin_img)
        align_64b = size % 8
        if align_64b:
            size += 8 - align_64b

        images_size.extend(size.to_bytes(4, 'little'))
        s_header.img_length += size
        f.close()

        # store image type information
        # TODO support other format
        bin_type = ENUM_BINARY_TYPE['ELF']
        images_type += bin_type.to_bytes(1, 'little')

        # Compute the hash table and add it to TLV blob
        hash_table = SegmentHash(img)
        hash_tlv.extend(hash_table.get_table())

    # Add image information
    # The 'IMGTYPE' contains a byte array of the image type (ENUM_BINARY_TYPE).
    # The 'IMGSIZE' contains a byte array of the size (32-bit) of each image.
    tlv.add('NUM_IMG', len(args.inf).to_bytes(1, 'little'))
    tlv.add('IMGTYPE', bytearray(images_type))
    tlv.add('IMGSIZE', bytearray(images_size))

    # Add hash type information in TLV blob
    # The 'HASHTYPE' TLV contains a byte associated to ENUM_HASH_TYPE.
    hash_type = ENUM_HASH_TYPE['SHA256']
    tlv.add('HASHTYPE', hash_type.to_bytes(1, 'little'))

    # Add hash table information in TLV blob
    # The HASHTABLE TLV contains a byte array containing all the elf segment
    # with associated hash.
    # TODO: add a sanity check to ensure that there is not segment overlap
    tlv.add('HASHTABLE', hash_tlv)

    # Add optional key information to TLV
    if args.key_infof:
        with open(args.key_infof, 'rb') as f:
            key_info = f.read()
        tlv.add('PKEYINFO', key_info)

    # Compute the Trailer containing TLV (with 64 bit alignment)
    trailer_buff = tlv.get()
    s_header.tlv_length = len(trailer_buff)

    # TODO: create a function for alignment
    align_64b = 8 - (s_header.tlv_length % 8)
    if align_64b:
        s_header.tlv_length += 8 - align_64b
        trailer_buff += bytearray(8 - align_64b)

    # Compute custom TLV that will provided to the platform PTA
    # Get list of custom protected TLVs from the command-line
    if args.plat_tlv:
        platform_tlv = custom_tlv()
        platform_tlv.generate_tlv(args.plat_tlv)
        s_header.plat_tlv_len = len(platform_tlv.tlv_buff)
        trailer_buff += platform_tlv.custom_tlvs.get()
        align_64b = 8 - (s_header.plat_tlv_len % 8)
        if align_64b:
            s_header.plat_tlv_len += 8 - align_64b
            trailer_buff += bytearray(8 - align_64b)

    dump_buffer(trailer_buff, name='TRAILER', indent="\t")

    # Signature chunk
    sign_size = sig_size_type.get(ENUM_SIGNATURE_TYPE[args.key_type],
                                  lambda: "Invalid sign type")(key)
    s_header.sign_length = sign_size

    # Construct the Header
    header = s_header.get_packed()

    # Generate signature
    signer = Signature.get(ENUM_SIGNATURE_TYPE[args.key_type])(key)

    signer.hash_compute(header)
    signer.hash_compute(trailer_buff)
    signature = signer.sign()
    if len(signature) != sign_size:
        raise Exception(("Actual signature length is not equal to ",
                         "the computed one: {} != {}".
                         format(len(signature), sign_size)))

    s_header.dump()

    with open(args.outf, 'wb') as f:
        f.write(header)
        f.write(signature)
        f.write(bytearray(sign_size - s_header.sign_length))
        for inputf in args.inf:
            with open(inputf, 'rb') as fin:
                bin_img = fin.read()
            f.write(bin_img)
            fin.close()
            align_64b = len(bin_img) % 8
            if align_64b:
                f.write(bytearray(8 - align_64b))
        f.write(trailer_buff)


if __name__ == "__main__":
    main()
