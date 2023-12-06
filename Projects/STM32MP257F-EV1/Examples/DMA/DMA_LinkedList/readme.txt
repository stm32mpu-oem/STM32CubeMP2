## <b>DMA_LinkedList Example Description</b>

-   How to use the DMA to perform a list of transfers. The transfer list is organized as linked-list,
	each time the current transfer ends the DMA automatically reload the next transfer parameters, and starts it (without CPU intervention).

-   This project is targeted to run on STM32MP257FAIx devices on STM32MP257F-EV1 board from STMicroelectronics.

-   At the beginning of the main program the HAL_Init() function is called to reset
	all the peripherals, initialize the Flash interface and the systick.
	Then the SystemClock_Config() function is used to configure the system clock (SYSCLK) to run at 160 MHz.

-   The Linked List is configured using the **DMA_LinkedListConfig** function.
	This function configures the DMA for a linked-list transfer which contains 3 nodes.
	All nodes are filled using HAL function **HAL_DMAEx_LinkedList_BuildNode**.
	Nodes are connected to the linked-list using the HAL function **HAL_DMAEx_LinkedList_InsertNode_Tail**.
	After setting all nodes parameters using **HAL_DMAEx_LinkedList_BuildNode()**/ **HAL_DMAEx_LinkedList_InsertNode_Tail()**,
	start the transfer in interrupt mode using **HAL_DMAEx_LinkedList_Start_IT()** function.
	Note that using the DMA, the transfer data length is always expressed in bytes whatever
	the source and destination data size (byte, half word or word).

-   At the end, the main program waits for the end of DMA transmission or error interrupts: the DMA transmission ends when all transfer nodes are served.

-   STM32MP257F-EV1 board's LED can be used to monitor the transfer status:
    -   **LED3 toggles** when no error detected.
    -   **LED3 turned ON** when any error occurred.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

DMA, Data Transfer, Memory to Memory, Channel, SRAM

### <b>Directory contents</b>

-   DMA/DMA_LinkedList/CM33/CM33/NonSecure/Src/main.c                    Main program
-   DMA/DMA_LinkedList/CM33/CM33/NonSecure/Src/stm32mp2xx_it.c           Interrupt handlers
-   DMA/DMA_LinkedList/CM33/CM33/NonSecure/Src/stm32mp2xx_hal_msp.c      HAL MSP module
-   DMA/DMA_LinkedList/CM33/CM33/NonSecure/Src/linked_list.c             LinkedList configuration file
-   DMA/DMA_LinkedList/CM33/CM33/NonSecure/Inc/main.h                    Main program header file
-   DMA/DMA_LinkedList/CM33/CM33/NonSecure/Inc/linked_list.h             LinkedList configuration header file
-   DMA/DMA_LinkedList/CM33/CM33/NonSecure/Inc/stm32mp2xx_hal_conf.h     HAL Configuration file
-   DMA/DMA_LinkedList/CM33/CM33/NonSecure/Inc/stm32mp2xx_it.h           Interrupt handlers header file

### <b>Hardware and Software environment</b>

-   This example runs on STM32MP257F-EV1 board.

-   This example has been tested with STM32MP257FAIx on STM32MP257F-EV1
    board and can be easily tailored to any other supported device
    and development board.

### <b>How to use it ?</b>
 
In order to make the program work, you must do the following:
- Open STM32CubeIDE
- Build with config: CA35TDCID_m33_ns_sign
- ssh root@192.168.7.1 'mkdir -p /home/root/DMA_LinkedList/lib/firmware'
- scp the signed firmware DMA_LinkedList_CM33_NonSecure_sign.bin to root@192.168.7.1:/home/root/DMA_LinkedList/lib/firmware
- scp the script Firmware/Utilities/scripts/fw_cortex_m33.sh to root@192.168.7.1:/home/root/DMA_LinkedList/
- To run the example on target: 
	On target shell run:
	- cd /home/root/DMA_LinkedList
	- ./fw_cortex_m33.sh start

