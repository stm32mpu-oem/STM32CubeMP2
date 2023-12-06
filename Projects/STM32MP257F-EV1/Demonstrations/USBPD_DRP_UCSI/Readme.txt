# USBPD_DRP_UCSI Build

For compilation please do following:
- export path of any arm cross compiler toolchain with `arm-none-eabi-gcc` to your PCs PATH environment Variable.
	- e.g. for STMCubeIDEs D3 Toolchain: C:\ST\STM32CubeIDE_1.12.0.23_MP2-D3\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.10.3-2021.10.win32_1.0.200.202301161003\tools\bin


To build:
- cmake -S ../../../../Middlewares/Third_Party/OpenAMP/libmetal/ -B build/libmetal  -G"Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=cmake/platforms/stm32mp-threadx-gcc.cmake
  cmake -G"Unix Makefiles" -B build
  make -C build

Output:
- Elf Binary: `USBPD_DRP_UCSI_CM33_NonSecure.elf` in build folder



