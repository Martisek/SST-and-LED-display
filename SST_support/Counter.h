/* 
 * File:   Counter.h
 * Author: martisek
 *
 * Created on 4. ?ervence 2017, 11:24
 */

#ifndef COUNTER_H
#define	COUNTER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include "sst_port.h"
    #include "Global_Task_def.h"
    
    #define CTR_SIG_OFFSET  20

    
    enum CounterSignal
    {
        CTR_INIT    = CTR_SIG_OFFSET + 0,   // 10
        CTR_TICK    = CTR_SIG_OFFSET + 1,   // 11
        CTR_UP      = CTR_SIG_OFFSET + 2,   // 12
        CTR_DOWN    = CTR_SIG_OFFSET + 3,   // 13
        CTR_NEWVAL  = CTR_SIG_OFFSET + 4    // 14
    };
    
    typedef enum CounterSignal CounterSignal;

    void SST_TaskCounter(SSTEvent e);

#ifdef	__cplusplus
}
#endif

#endif	/* COUNTER_H */

