/* 
 * File:   FSM.c
 * Author: martisek
 *
 * Created on May 9, 2017, 4:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FSM.h" /* the port of the QEP event processor */

QEvent const QEP_reservedEvt_[] = {
    { (QSignal)QEP_EMPTY_SIG_, (uint8_t)0 },
    { (QSignal)Q_ENTRY_SIG,    (uint8_t)0 },
    { (QSignal)Q_EXIT_SIG,     (uint8_t)0 },
    { (QSignal)Q_INIT_SIG,     (uint8_t)0 }
};

void QFsm_init(QFsm *me, QEvent const *e)
{
    (*me->state)(me, e); /* execute the top-most initial transition */
    (void)(*me->state)(me , &QEP_reservedEvt_[Q_ENTRY_SIG]);    /* enter the target */

    return;
}

void QFsm_dispatch(QFsm *me, QEvent const *e)
{
    QStateHandler s = me->state; /* save the current state */
    QState r = (s)(me, e); /* call the event handler */

    if (r == Q_RET_TRAN)
        { /* transition taken? */

            (void)(*s)(me, &QEP_reservedEvt_[Q_EXIT_SIG]); /* exit the source */
            (void)(*me->state)(me,&QEP_reservedEvt_[Q_ENTRY_SIG]); /*enter target*/
        }
    return;
}

