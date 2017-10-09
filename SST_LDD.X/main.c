/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.26
        Device            :  PIC24FJ128GA204
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.30
        MPLAB             :  MPLAB X 3.45
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mcc_generated_files/mcc.h"
#include "Global_Task_def.h"
#include "LEDDisplay_Driver.h"
#include "Counter.h"
#include "sst_port.h"

SSTEvent LEDD_Queue[TSK_LDD_QUEUE_L];
SSTEvent CTRD_Queue[TSK_CTR_QUEUE_L];

uint8_t CapData[] = {125, 10, 88, 47};


/*
                         Main application
 */

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    SST_task(SST_TaskLDD, TASK_LDD_PRIO, LEDD_Queue, TSK_LDD_QUEUE_L, LDD_INIT, 0);
    SST_task(SST_TaskCounter, TASK_CTR_PRIO, CTRD_Queue, TSK_CTR_QUEUE_L, CTR_INIT, 0);
    
    I2C1_MESSAGE_STATUS I2C_state;
    
    I2C1_MasterWrite(CapData, sizeof(CapData)/sizeof(CapData[0]), 0x21, &I2C_state);
          

    SST_run();

    return -1;
}
/**
 End of File
*/


/*
 #include <xc.h>
#include "tmr1.h"
#include "sst.h"
#include "Counter.h"
#include "Global_Task_def.h"
#include "LEDDisplay_Driver.h"
 * 
 *  uint8_t stav;
    static uint16_t counter_1s;
    
    stav = SST_post(TASK_LDD_PRIO, LDD_TICK, 0);
    
    counter_1s ++;
    if (counter_1s >= 200)
    {
        counter_1s = 0;
        stav = SST_post(TASK_CTR_PRIO, CTR_TICK, 0);
    }
 
 
 
 */

/*
 uint8_t stav;
    static uint16_t counter_1s;
    uint16_t portValue;
    static uint16_t lastPortValue = 0;
    static uint16_t keyState = IDLE;
    static uint16_t keyCounter = 0;
    
    stav = SST_post(TASK_LDD_PRIO, LDD_TICK, 0);    // Display tick event
    
    counter_1s ++;
    if (counter_1s >= 200)
    {
        counter_1s = 0;
        stav = SST_post(TASK_CTR_PRIO, CTR_TICK, 0);
    }
    
    portValue = PORTC & KEY_PC_MASK;
    
    switch (keyState)
    {
        case IDLE:          if ((portValue ^ KEY_PC_MASK) != 0)
                            {
                                lastPortValue = portValue;
                                keyState = DEBOUNCING;
                            }
                            break;
        
        case DEBOUNCING:    keyCounter ++;
                            if (keyCounter >= KEY_CONFIRM_DLY && lastPortValue == portValue)
                            {
                                keyCounter = 0;
                                stav = SST_post(TASK_CTR_PRIO, CTR_UP, 0);
                                keyState = PRESSED;
                                
                            }
                            break;
                            
        case PRESSED:       if (lastPortValue != portValue) 
                                    keyState = IDLE;
                            break;
                                
                            
    }
 
 */