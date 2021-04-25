/*
 * Amazon FreeRTOS Demo Bootloader V1.4.8
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */


/**
 * @file aws_boot_pal.c
 * @brief Bootloader platform code.
 */

/* Microchip framework includes. */
#include "aws_boot_nvm.h"
#include "bsp/bsp.h"
/* Bootloader includes. */
#include "aws_boot_types.h"
#include "aws_boot_pal.h"
#include "aws_boot_partition.h"
#include "aws_boot_loader.h"
#include "aws_boot_log.h"

/*-----------------------------------------------------------*/

void BOOT_PAL_LaunchApplication( const void * const pvLaunchAddress )
{
    uint32_t msp            = *(uint32_t *)(pvLaunchAddress);
    uint32_t reset_vector   = *(uint32_t *)(pvLaunchAddress + 4);
    void ( * pfApplicationEntry )( void ) = ( void ( * )( void ) )pvLaunchAddress;
    if (msp == 0xffffffff)
    {
        BOOT_LOG_L1( "\n] msp is invalid!!!. \r\n");
        while(1);
    }

    __set_MSP(msp);

    asm("bx %0"::"r" (reset_vector));
     //( *pfApplicationEntry )();
}

/*-----------------------------------------------------------*/

void BOOT_PAL_LaunchApplicationDesc( const BOOTImageDescriptor_t * const pvLaunchDescriptor )
{
    DEFINE_BOOT_METHOD_NAME( "BOOT_PAL_LaunchApplicationDesc" );

    void * pvExecAddress = pvLaunchDescriptor->pvExecAddress;

    /* The microchip flash is organized in two memory banks and it should
     * be toggled depending on if we are executing from lower or upper bank.
     */
    if( pvLaunchDescriptor >= ( BOOTImageDescriptor_t * ) ( FLASH_DEVICE_BASE + FLASH_PARTITION_OFFSET_IMAGE_1 ) )
    {
        /* Executing from upper bank so toggle.*/
        AWS_NVM_ToggleFlashBanks();

        BOOT_LOG_L1( "\n[%s] Memory banks are swapped. \r\n", BOOT_METHOD_NAME );
    }
    pvExecAddress=0x8000;
    BOOT_PAL_LaunchApplication( pvExecAddress );
}

/*-----------------------------------------------------------*/

BaseType_t BOOT_PAL_WatchdogInit( void )
{
    return pdTRUE;
}

/*-----------------------------------------------------------*/

BaseType_t BOOT_PAL_WatchdogEnable( void )
{
    BaseType_t xReturn = pdFALSE;
    WDT_Enable();
    return xReturn;
}

/*-----------------------------------------------------------*/

BaseType_t BOOT_PAL_WatchdogDisable( void )
{
    BaseType_t xReturn = pdFALSE;
    WDT_Disable();
    return xReturn;
}

/*-----------------------------------------------------------*/

void BOOT_PAL_NotifyBootError( void )
{
    uint32_t ulCntr = 0;
    uint32_t ulFastBlink = 10000000;

    /* Keep flashing LED. */
    for( ; ; )
    {
        /* Fast blink. */
        if( ulCntr++ == ulFastBlink )
        {
           LED_Toggle();
            ulCntr = 0;
        }
    }
}
