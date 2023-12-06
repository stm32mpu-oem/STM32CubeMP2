
## <b>Fx_SRAM_File_Edit_Standalone Application Description</b>

This application provides an example of FileX stack usage on STM32MP257F-EV1 board, running in standalone mode (without ThreadX). It demonstrates how to create a Fat File system on the internal SRAM memory using FileX API.

The application is designed to execute file operations on the SRAM-Disk device, it provides all required software code for properly managing it.

The application's main calls the MX_FileX_Init() function in order to Initialize FileX, format the SRAM memory as FAT and open the sram_disk driver. The resulting file system is a FAT32 compatible, with 512 bytes per sector.

Upon successful opening of the created SRAM-Disk media, FileX continues with creating a file called "STM32.TXT" into the root directory by calling MX_FileX_Process(VOID *arg) function, then writes into it some predefined data. The file is re-opened in read only mode and content is checked.


As stated earlier, the present application runs in standalone mode without ThreadX, for this reason, the standalone variant of fileX is used, plus the following flags need to be set in fx_user.h:

  #define FX_SINGLE_THREAD

  #define FX_STANDALONE_ENABLE

#### <b>Expected success behavior</b>

Successful operation is marked by a toggling orange led (LED3) light at 500ms.

Also, information regarding executing operation on the SRAM-Disk is printed to the serial port.

#### <b>Error behaviors</b>

On failure, the orange led (LED3) will be stay turned ON for ever.

#### <b>Assumptions if any</b>
None

#### <b>Known limitations</b>
None

### <b>Notes</b>


 1. The created SRAM-Disk, is placed in SRAM starting from the(SRAM1_BASE=@0x30040000).
 2. User can change the location of the SRAM-Disk by modifying FX_SRAM_DISK_BASE_ADDRESS.

#### <b>FileX/LevelX usage hints</b>

- When calling the fx_media_format() API, it is highly recommended to understand all the parameters used by the API to correctly generate a valid filesystem.

### <b>Keywords</b>

FileX, File System, FAT32, SRAM

### <b>Hardware and Software environment</b>

  - This application runs on STM32MP257F-EV1 devices.
  - This application has been tested with STMicroelectronics STM32MP257F-EV1 boards.
    and can be easily tailored to any other supported device and development board.

  - This application uses UART5 to display logs, the hyperterminal configuration is as follows:

      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - Stop Bit = 1
      - Parity = none
      - Flow control = None


### <b>How to use it ?</b>

In order to make the program work, you must do the following:

  - Open STM32CubeIDE
  - Build with config: CA35TDCID_m33_ns_sign
  - ssh root@192.168.7.1 'mkdir -p /home/root/Tx_Thread_Creation/lib/firmware'
  - scp the signed firmware Fx_SRAM_File_Standalone_CM33_NonSecure_sign.bin to root@192.168.7.1:/home/root/ Fx_SRAM_File_Standalone/lib/firmware
  - scp the script Firmware/Utilities/scripts/fw_cortex_m33.sh to root@192.168.7.1:/home/root/ Fx_SRAM_File_Standalone/
  - To run the example on target: 
	  On target shell run:
	    - cd /home/root/ Fx_SRAM_File_Standalone
		- ./fw_cortex_m33.sh start
