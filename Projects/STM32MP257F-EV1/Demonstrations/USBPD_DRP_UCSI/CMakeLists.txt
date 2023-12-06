cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "util/arm-gcc-toolchain.cmake")
set(BASE_DIR "${CMAKE_CURRENT_LIST_DIR}/")
set(CMAKE_BINARY_DIR "${BASE_DIR}build")
project(USBPD_DRP_UCSI_CM33_NonSecure C ASM)

add_definitions() 
include(util/cortex-m33-stm32mp2.cmake)
include(util/color.cmake)
message("-- Starting Cmake compilation ${LINKER_SCRIPT} ${CMAKE_BINARY_DIR}")

set(DEFINITIONS "-DSTM32MP257Cxx -DLOGLEVEL=4 -DUSE_FULL_LL_DRIVER -DTX_SINGLE_MODE_NON_SECURE=1 \
-DTX_INCLUDE_USER_DEFINE_FILE -D__LOG_UART_IO_ -DUSE_STM32MP257F_EV1 -DNO_ATOMIC_64_SUPPORT -DMETAL_INTERNAL -DVIRTIO_DEVICE_ONLY \
-DMETAL_MAX_DEVICE_REGIONS=2 -DLINUX_RPROC_MASTER -DCORE_CM33 -DUSE_HAL_DRIVER -DTCPP0203_SUPPORT -DUSBPD_PORT_COUNT=1 -DUSBPD_THREADX \
-D_DRP -D_TRACE -DUSBPDCORE_LIB_PD3_FULL -D_SRC_CAPA_EXT")
set(TARGET USBPD_DRP_UCSI_CM33_NonSecure)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS} ${COMMON_COMPILE_FLAGS} -T${LINKER_SCRIPT} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${COMMON_COMPILE_FLAGS} -DSTM32MP257Cxx -DTX_SINGLE_MODE_NON_SECURE=1")
set(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS}")
set(HAL_SRC_FILES ${HAL_SRC_FILES}
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_adc.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_adc_ex.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_cortex.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_dma.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_dma_ex.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_exti.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_gpio.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_i2c.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_i2c_ex.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_icache.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_ipcc.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_pwr.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_pwr_ex.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_rcc.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_rcc_ex.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_tim.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_tim_ex.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_hal_uart.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_ll_dma.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_ll_exti.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_ll_gpio.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_ll_rcc.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_ll_ucpd.c 
						${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Src/stm32mp2xx_ll_usart.c 
						)
set(OPENAMP_SRC_FILES ${OPENAMP_SRC_FILES}
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/virtual_driver/virt_i2c.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/virtual_driver/virt_intc.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/virtual_driver/virt_uart.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/open-amp/lib/remoteproc/remoteproc_virtio.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg/rpmsg.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg/rpmsg_virtio.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/system/threadx/alloc.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/system/threadx/condition.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/system/threadx/threadx_device.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/system/threadx/threadx_init.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/system/threadx/threadx_shmem.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/system/threadx/time.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/device.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/init.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/io.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/log.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/shmem.c 
						${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/lib/system/threadx/sys.c 
						)
set(THREADX_SRC_FILES ${THREADX_SRC_FILES}
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_block_allocate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_block_pool_cleanup.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_block_pool_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_block_pool_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_block_pool_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_block_pool_initialize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_block_pool_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_block_release.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_allocate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_pool_cleanup.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_pool_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_pool_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_pool_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_pool_initialize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_pool_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_pool_search.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_byte_release.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_event_flags_cleanup.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_event_flags_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_event_flags_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_event_flags_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_event_flags_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_event_flags_initialize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_event_flags_set.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_event_flags_set_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_initialize_high_level.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_initialize_kernel_enter.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_initialize_kernel_setup.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_cleanup.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_initialize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_priority_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_mutex_put.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_cleanup.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_flush.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_front_send.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_initialize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_receive.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_send.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_queue_send_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_ceiling_put.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_cleanup.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_initialize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_put.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_semaphore_put_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_entry_exit_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_identify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_initialize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_preemption_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_priority_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_relinquish.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_reset.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_resume.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_shell_entry.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_sleep.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_stack_analyze.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_stack_error_handler.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_stack_error_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_suspend.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_system_preempt_check.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_system_resume.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_system_suspend.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_terminate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_time_slice.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_time_slice_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_timeout.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_thread_wait_abort.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_time_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_time_set.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_activate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_deactivate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_expiration_process.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_initialize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_system_activate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_system_deactivate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/tx_timer_thread_entry.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_block_allocate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_block_pool_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_block_pool_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_block_pool_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_block_pool_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_block_release.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_byte_allocate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_byte_pool_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_byte_pool_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_byte_pool_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_byte_pool_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_byte_release.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_event_flags_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_event_flags_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_event_flags_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_event_flags_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_event_flags_set.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_event_flags_set_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_mutex_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_mutex_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_mutex_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_mutex_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_mutex_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_mutex_put.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_flush.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_front_send.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_receive.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_send.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_queue_send_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_semaphore_ceiling_put.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_semaphore_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_semaphore_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_semaphore_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_semaphore_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_semaphore_prioritize.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_semaphore_put.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_semaphore_put_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_entry_exit_notify.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_preemption_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_priority_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_relinquish.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_reset.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_resume.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_suspend.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_terminate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_time_slice_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_thread_wait_abort.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_timer_activate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_timer_change.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_timer_create.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_timer_deactivate.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_timer_delete.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/common/src/txe_timer_info_get.c 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_context_restore.S 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_context_save.S 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_interrupt_control.S 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_schedule.S 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_stack_build.S 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_thread_system_return.S 
						${BASE_DIR}/../../../../Middlewares/ST/threadx/ports/cortex_m33/gnu/src/tx_timer_interrupt.S 						
						)
set(BSP_SRC_FILES ${BSP_SRC_FILES}
						${BASE_DIR}/../../../../Drivers/BSP/STM32MP257F-EV1/stm32mp257f_eval.c 
						${BASE_DIR}/../../../../Drivers/BSP/STM32MP257F-EV1/stm32mp257f_eval_bus.c 
						${BASE_DIR}/../../../../Drivers/BSP/STM32MP257F-EV1/stm32mp257f_eval_pmic.c 
						${BASE_DIR}/../../../../Drivers/BSP/STM32MP257F-EV1/stm32mp257f_eval_usbpd_pwr.c  
						${BASE_DIR}/../../../../Drivers/BSP/Components/tcpp0203/tcpp0203.c 
						${BASE_DIR}/../../../../Drivers/BSP/Components/tcpp0203/tcpp0203_reg.c 
						)
set(USBPDLIB_SRC_FILES
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/UCSI/ppm.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/UCSI/usbpd_ucsi_ppm.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STM32MP2XX/src/usbpd_cad_hw_if.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STM32MP2XX/src/usbpd_hw.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STM32MP2XX/src/usbpd_hw_if_it.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STM32MP2XX/src/usbpd_phy.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STM32MP2XX/src/usbpd_phy_hw_if.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STM32MP2XX/src/usbpd_pwr_hw_if.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STM32MP2XX/src/usbpd_timersserver.c 
						${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Core/src/usbpd_trace.c 
						)
set(UTILS_SRC_FILES ${UTILS_SRC_FILES}
						${BASE_DIR}/../../../../Utilities/TRACER_EMB/tracer_emb.c 
						${BASE_DIR}/../../../../Utilities/ResourcesManager/res_mgr.c 
						${BASE_DIR}/../../../../Utilities/CoproSync/copro_sync.c
						${BASE_DIR}/../../../../Utilities/TRACER_EMB/tracer_emb_hw.c
						${BASE_DIR}/../../../../Utilities/Services/GenericServices/threadx_syscalls.c
						)
set(CMSIS_SRC_FILES ${CMSIS_SRC_FILES}
						${BASE_DIR}/../../../../Drivers/CMSIS/Device/ST/STM32MP2xx/Source/Templates/system_stm32mp2xx_m33_ns.c
						${BASE_DIR}/../../../../Drivers/CMSIS/Device/ST/STM32MP2xx/Source/Templates/gcc/startup_stm32mp257cxx_m33.s
						)
# Set application source files
set(APPLICATION_SRC ${APPLICATION_SRC} ${HAL_SRC_FILES} ${OPENAMP_SRC_FILES} ${THREADX_SRC_FILES} ${BSP_SRC_FILES} ${USBPDLIB_SRC_FILES} ${UTILS_SRC_FILES} ${CMSIS_SRC_FILES}
						${BASE_DIR}/CM33/NonSecure/AZURE_RTOS/App/app_azure_rtos.c
						${BASE_DIR}/CM33/NonSecure/Core/Src/app_threadx.c 
						${BASE_DIR}/CM33/NonSecure/Core/Src/led_threadx.c 
						${BASE_DIR}/CM33/NonSecure/Core/Src/tx_initialize_low_level.S
						${BASE_DIR}/CM33/NonSecure/Core/Src/main.c 
						${BASE_DIR}/CM33/NonSecure/Core/Src/syscalls.c
						${BASE_DIR}/CM33/NonSecure/Core/Src/stm32mp2xx_hal_msp.c 
						${BASE_DIR}/CM33/NonSecure/Core/Src/stm32mp2xx_hal_timebase_tim.c 
						${BASE_DIR}/CM33/NonSecure/Core/Src/stm32mp2xx_it.c 
						${BASE_DIR}/CM33/NonSecure/OpenAMP/Src/mbox_ipcc.c 
						${BASE_DIR}/CM33/NonSecure/OpenAMP/Src/openamp.c 
						${BASE_DIR}/CM33/NonSecure/OpenAMP/Src/openamp_log.c 
						${BASE_DIR}/CM33/NonSecure/OpenAMP/Src/openamp_threadx.c 
						${BASE_DIR}/CM33/NonSecure/OpenAMP/Src/rsc_table.c 
						${BASE_DIR}/CM33/NonSecure/USBPD/App/usbpd.c 
						${BASE_DIR}/CM33/NonSecure/USBPD/App/usbpd_dpm_core.c 
						${BASE_DIR}/CM33/NonSecure/USBPD/App/usbpd_pwr_if.c 
						${BASE_DIR}/CM33/NonSecure/USBPD/App/usbpd_threadx.c 
						${BASE_DIR}/CM33/NonSecure/USBPD/App/usbpd_ucsi_if.c 
						${BASE_DIR}/CM33/NonSecure/USBPD/Target/usbpd_dpm_user.c 
						${BASE_DIR}/CM33/NonSecure/USBPD/Target/usbpd_pwr_user.c 
						${BASE_DIR}/CM33/NonSecure/USBPD/Target/usbpd_vdm_user.c)

include_directories(APPLICATION_INCLUDE ${BASE_DIR}/CM33/NonSecure/Core/Inc) 
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/CM33/NonSecure/USBPD/App )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/CM33/NonSecure/USBPD/Target )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/CM33/NonSecure/OpenAMP/Inc )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/CM33/NonSecure/AZURE_RTOS/App )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Drivers/CMSIS/Device/ST/STM32MP2xx/Include )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Drivers/CMSIS/Core/Include )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Utilities/TRACER_EMB )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Utilities/CoproSync )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Utilities/ResourcesManager )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Drivers/BSP/STM32MP257F-EV1 )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Drivers/BSP/Components/stpmic2 )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Drivers/STM32MP2xx_HAL_Driver/Inc )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Middlewares/ST/threadx/common/inc )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STM32MP2XX/inc )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/UCSI )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/build/libmetal/lib/include )
include_directories(APPLICATION_INCLUDE ${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/virtual_driver)

set(SOURCE_FILES ${APPLICATION_SRC} ${LINKER_SCRIPT} )
add_custom_target(TARGET
    ALL
        COMMAND ${CMAKE_COMMAND} -S ${BASE_DIR}/../../../../Middlewares/Third_Party/OpenAMP/libmetal/ -B libmetal  -G'Unix Makefiles' -DCMAKE_TOOLCHAIN_FILE=cmake/platforms/stm32mp-threadx-gcc.cmake

)
link_directories(${CMAKE_SOURCE_DIR}/../../../../Middlewares/ST/STM32_USBPD_Library/Core/lib)
add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${LINKER_SCRIPT})
target_link_libraries(${PROJECT_NAME}.elf :USBPDCORE_PD3_FULL_CM33_wc32.a)
#target_link_libraries(${PROJECT_NAME}.elf PUBLIC)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map -Wl,--gc-sections -static  -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -z max-page-size=4096 -lc -lm -Wl,--end-group")
add_custom_command(TARGET ${TARGET}.elf POST_BUILD
     COMMAND ${TOOLCHAIN_PREFIX}objcopy -Oihex ${TARGET}.elf ${TARGET}.hex
     COMMAND ${TOOLCHAIN_PREFIX}objcopy -Obinary ${TARGET}.elf ${TARGET}.bin
     COMMAND ${TOOLCHAIN_PREFIX}size --format=berkeley ${TARGET}.elf
     COMMAND ${TOOLCHAIN_PREFIX}objcopy -S ${TARGET}.elf ${TARGET}_stripped.elf
     #COMMAND python ${BASE_DIR}/../../../../Utilities/optee_os/scripts/sign_rproc_fw.py --in ${TARGET}_stripped.elf --out ${TARGET}_sign.bin --key ${BASE_DIR}/../../../../Utilities/optee_os/keys/default_rproc.pem --plat-tlv NSBOOTADDR 0x80100000
     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
