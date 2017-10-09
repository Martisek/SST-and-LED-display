/* 
 * File:   FSM.h
 * Author: martisek
 *
 * Created on May 9, 2017, 4:35 PM
 */

#ifndef FSM_H
#define	FSM_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    

/* qevent.h --------------------------------------------------------------------------------*/
typedef uint8_t QSignal;

typedef struct QEventTag
{
    /* the event structure */
    QSignal sig;        /* signal of the event */
    uint8_t dynamic_;   /* dynamic attribute of the event (0 for static) */
} QEvent;


/* qep.h -----------------------------------------------------------------------------------*/
typedef uint8_t QState; /* status returned from a state-handler function */
typedef QState (*QStateHandler)(void *me, QEvent const *e); /* pointer to function type definition */


typedef struct QFsmTag
{
    /* Finite State Machine */
    QStateHandler state; /* current active state */
} QFsm;

#define QFsm_ctor(me_, initial_) ((me_)->state = (initial_))
#define Q_TRAN(target_) (((QFsm *)me)->state = (QStateHandler)(target_), Q_RET_TRAN)


void QFsm_init (QFsm *me, QEvent const *e);
void QFsm_dispatch(QFsm *me, QEvent const *e);

#define Q_RET_HANDLED   ((QState)0)
#define Q_RET_IGNORED   ((QState)1)
#define Q_RET_TRAN      ((QState)2)
#define Q_HANDLED()     (Q_RET_HANDLED)
#define Q_IGNORED()     (Q_RET_IGNORED)



enum QReservedSignals
{
    QEP_EMPTY_SIG_ = 0,
    Q_ENTRY_SIG    = 1, /* signal for coding entry actions */
    Q_EXIT_SIG     = 2, /* signal for coding exit actions */
    Q_INIT_SIG     = 3, /* signal for coding initial transitions */
    Q_USER_SIG     = 4  /* first signal that can be used in user applications */
};



#ifdef	__cplusplus
}
#endif

#endif	/* FSM_H */

