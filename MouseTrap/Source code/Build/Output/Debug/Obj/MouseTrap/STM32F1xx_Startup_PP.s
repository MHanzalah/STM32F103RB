# 1 "C:\\Users\\M Hanzalah\\Documents\\Embedded\\STM32F103RB\\MouseTrap\\Source code\\Src\\BSP\\MCU\\STM32F1xx\\Source\\STM32F1xx_Startup.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:\\Users\\M Hanzalah\\Documents\\Embedded\\STM32F103RB\\MouseTrap\\Source code\\Src\\BSP\\MCU\\STM32F1xx\\Source\\STM32F1xx_Startup.s"
# 78 "C:\\Users\\M Hanzalah\\Documents\\Embedded\\STM32F103RB\\MouseTrap\\Source code\\Src\\BSP\\MCU\\STM32F1xx\\Source\\STM32F1xx_Startup.s"
        .syntax unified
# 101 "C:\\Users\\M Hanzalah\\Documents\\Embedded\\STM32F103RB\\MouseTrap\\Source code\\Src\\BSP\\MCU\\STM32F1xx\\Source\\STM32F1xx_Startup.s"
        .global reset_handler
        .global Reset_Handler
        .equ reset_handler, Reset_Handler
        .section .init.Reset_Handler, "ax"
        .balign 2
        .thumb_func
Reset_Handler:




        bl SystemInit
# 164 "C:\\Users\\M Hanzalah\\Documents\\Embedded\\STM32F103RB\\MouseTrap\\Source code\\Src\\BSP\\MCU\\STM32F1xx\\Source\\STM32F1xx_Startup.s"
        b _start





        .weak SystemInit





        .section .init_array, "aw"
        .balign 4
        .word SystemCoreClockUpdate
# 197 "C:\\Users\\M Hanzalah\\Documents\\Embedded\\STM32F103RB\\MouseTrap\\Source code\\Src\\BSP\\MCU\\STM32F1xx\\Source\\STM32F1xx_Startup.s"
        .weak HardFault_Handler
        .section .init.HardFault_Handler, "ax"
        .balign 2
        .thumb_func
HardFault_Handler:



        ldr R1, =0xE000ED2C
        ldr R2, [R1]
        cmp R2, #0

hfLoop:
        bmi hfLoop
# 225 "C:\\Users\\M Hanzalah\\Documents\\Embedded\\STM32F103RB\\MouseTrap\\Source code\\Src\\BSP\\MCU\\STM32F1xx\\Source\\STM32F1xx_Startup.s"
        tst LR, #4
        ite eq
        mrseq R0, MSP
        mrsne R0, PSP
# 239 "C:\\Users\\M Hanzalah\\Documents\\Embedded\\STM32F103RB\\MouseTrap\\Source code\\Src\\BSP\\MCU\\STM32F1xx\\Source\\STM32F1xx_Startup.s"
        orr R2, R2, #0x80000000
        str R2, [R1]




        ldr R1, [R0, #24]
        adds R1, #2
        str R1, [R0, #24]

        bx LR
