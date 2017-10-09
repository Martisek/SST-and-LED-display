/* 
 * File:   main.c
 * Author: martisek
 *
 * Created on 3. ?ervence 2017, 11:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Global_Task_def.h"
#include "sst_port.h"
#include "sst.h"
#include "LEDDisplay_Driver.h"


SSTEvent LEDD_Queue[TSK_LDD_QUEUE_L];

/*
 * 
 */
int main(int argc, char** argv) {

    
    SST_task(SST_TaskLDD, TASK_LDD_PRIO, LEDD_Queue, TSK_LDD_QUEUE_L, LDD_INIT, 0);
    
    return (EXIT_SUCCESS);
}

