/*
 * File:   LEDDisplay_Driver.c
 * Author: martisek
 *
 * Created on July 4, 2017, 3:19 PM
 */


#include "xc.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Counter.h"
#include "LEDDisplay_Driver.h"

/* Globalni promenna */
static uint16_t CounterValue;

/* Public fce*/
void SST_TaskCounter(SSTEvent e);


#ifdef MYDEBUG
    const char SST_CounterInit[] = "Counter is initialized...";
    const char SST_CounterTick[] = "Counter is counting...";
    const char SST_CounterDown[] = "Value of counter is decreased...";
    const char SST_CounterUp[]   = "Value of counter is increased...";
    
    char DebugInfoStringCTR[30];
#endif


/*============================================================================*/

void SST_TaskCounter(SSTEvent e)
{
    switch (e.sig)
    {
        case CTR_INIT:  CounterValue = 0;
                        #ifdef MYDEBUG
                            strcpy(DebugInfoStringCTR, SST_CounterInit);
                        #endif
                        break;
                        
        case CTR_TICK:  CounterValue ++;
                        if (CounterValue >= 1000)
                            CounterValue = 0;
                        SST_post(TASK_LDD_PRIO, LDD_NEWVAL, CounterValue);
                        #ifdef MYDEBUG
                            strcpy(DebugInfoStringCTR, SST_CounterTick);
                        #endif
                        break;
                        
        case CTR_UP:    CounterValue = CounterValue + 10;
                        if (CounterValue >= 1000)
                            CounterValue = 0;
                        SST_post(TASK_LDD_PRIO, LDD_NEWVAL, CounterValue);
                        #ifdef MYDEBUG
                            strcpy(DebugInfoStringCTR, SST_CounterUp);
                        #endif
                        break;
                        
        case CTR_DOWN:  if (CounterValue > 0)
                        {
                            CounterValue --;
                            SST_post(TASK_LDD_PRIO, LDD_NEWVAL, CounterValue);
                        }
                        #ifdef MYDEBUG
                            strcpy(DebugInfoStringCTR, SST_CounterDown);
                        #endif
                        break;
              
        default:        break;
          
    }
    return;
}