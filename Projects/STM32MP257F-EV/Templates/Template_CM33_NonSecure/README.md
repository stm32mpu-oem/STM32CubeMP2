## <b>Template_CM33_NonSecure Application Description</b>
-   This project provides a reference template based on the STM32Cube HAL API that can be used to build any firmware application
   
####  <b>Expected success behavior</b>
- Print message in UART console
- Blink LED3 (orange) led every 1s

#### <b>Error behaviors</b>
- No print in UART console, No LED3 blink

### <b>Directory contents</b>

  - Src/main.c                      Main program source file
  - Src/stm32mp2xx_it.c             Interrupt handlers source file
  - Src/stm32mp2xx_hal_msp.c        HAL MSP module
  - Src/syscalls.c                  STM32MP2xx system clock configuration file
  - Inc/main.h                      Main program header file
  - Inc/stm32mp2xx_hal_conf.h       HAL Configuration file
  - Inc/stm32mp2xx_it.h             Interrupt handlers header file
  - Inc/stm32mp257f_eval_conf.h     STM32MP257-EV1 board configuration file

### <b>Hardware and Software environment</b>

  - This example runs on STM32MP25xx devices
  - This example has been tested with STMicroelectronics STM32MP257F-EV1.
    and can be easily tailored to any other supported device and development board.

  - Connect ST-Link cable to the PC USB port to display trace

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application
 - Connect a type C device on the Type-C connector 21