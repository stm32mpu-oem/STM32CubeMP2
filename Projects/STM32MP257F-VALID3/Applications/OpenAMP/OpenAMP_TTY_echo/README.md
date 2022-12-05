## <b>SAI_AudioPlay Example Description</b>

How to  play an audio file via SAI using DMA circular mode.

      Plug a headphone to ear the sound  /!\ Take care of yours ears.
      Default volume is 80%.
      The audio file is played in loop
      @Note: Copy file 'audio.bin' (available in AudioFile directly) in the SYSRAM if SYRAM not used 
      at @0x0A00C800 using Linker script stm32mp25xx_SRAM_m33_ns.ld or STM32CubeProgrammer.

This project is targeted to run on STM32MP257xx devices on STM32257XX-VALIDX board from STMicroelectronics.
The project configures the maximum clock frequency for PLL5 at 1,344 GHz.

STM32MP257XX-VALIDX board's LED can be used to monitor the project operation status:

!!!!!!!!!!!!!!!!section LED should be updated !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     - LED_GREEN  toggle when no error detected. LED2 
     - LED_RED  is ON when any project error was occurred. LED3 


#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

### <b>Keywords</b>

Audio, SAI, DMA, Buffer update, play, headphone, audio protocol

### <b>Directory contents</b>

  - SAI/SAI_AudioPlay/Src/linked_list.c               Linked list source file
  - SAI/SAI_AudioPlay/Src/main.c                      Main program source file
  - SAI/SAI_AudioPlay/Src/stm32mp2xx_it.c             Interrupt handlers source file
  - SAI/SAI_AudioPlay/Src/stm32mp2xx_hal_msp.c        HAL MSP module
  - SAI/SAI_AudioPlay/Src/system_stm32mp2xx.c         STM32MP2xx system clock configuration file
  - SAI/SAI_AudioPlay/Src/linked_list.h               Linked list header file
  - SAI/SAI_AudioPlay/Inc/main.h                      Main program header file
  - SAI/SAI_AudioPlay/Inc/stm32mp2xx_hal_conf.h       HAL Configuration file
  - SAI/SAI_AudioPlay/Inc/stm32mp2xx_it.h             Interrupt handlers header file
  - SAI/SAI_AudioPlay/Inc/stm32mp257xx_validx_conf.h  STM32MP2257-VALIDX board configuration file

### <b>Hardware and Software environment</b>

  - This example runs on STM32MP257xx devices without security enabled (TZEN=0).

  - This example has been tested with STMicroelectronics STM32MP2257-VALIDX (MB1703-01)
    board and can be easily tailored to any other supported device
    and development board.

  - Plug headset on CN20 connector (Headset).

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

