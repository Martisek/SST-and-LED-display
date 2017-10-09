/*
 * File:   LEDDisplay_Driver.c
 * Author: martisek
 *
 * Created on March 9, 2017, 3:19 PM
 */


#include "xc.h"
#include "LEDDisplay_Driver.h"
#include <string.h>


/**==========================================================================**/
/* Public function prototypes */

void SST_TaskLDD(SSTEvent e);

/**==========================================================================**/
/* Private function prototypes */
static void DisplayCtor(DisplayDriver *me);
static QState DisplayInit(DisplayDriver *me, QEvent const *e);

static QState DisplaySegOnes(DisplayDriver *me, QEvent const *e);
static QState DisplaySegTens(DisplayDriver *me, QEvent const *e);
static QState DisplaySegHundreds(DisplayDriver *me, QEvent const *e);
static QState DisplaySegThousands(DisplayDriver *me, QEvent const *e);
static QState DisplayOFF(DisplayDriver *me, QEvent const *e);

static void Double_dabble(DisplayDriver *me, uint16_t binvalue);
static LEDDD_State LDD_Char2SegmentConvert(char value);

/* Global variables*/
static DisplayDriver LEDDisplay;
static DisplayEvent  LEDDisplayEvt;


#ifdef MYDEBUG
    const char SegOnesEnterString[] = "Seg ones is entering...";
    const char SegTensEnterString[] = "Seg tens is entering...";
    const char SegHunsEnterString[] = "Seg huns is entering...";
    const char SegThosEnterString[] = "Seg thos is entering...";
    
    const char SegOnesExitString[] = "Seg ones is exiting...";
    const char SegTensExitString[] = "Seg tens is exiting...";
    const char SegHunsExitString[] = "Seg huns is exiting...";
    const char SegThosExitString[] = "Seg thos is exiting...";
    
    
    char DebugInfoStringLDD[30];
#endif
  
/**==========================================================================**/
/* Public functions */
 void SST_TaskLDD(SSTEvent e)
{
    switch (e.sig)
    {
        case LDD_INIT:      Double_dabble(&LEDDisplay, 0);
                            DisplayCtor(&LEDDisplay);
                            QFsm_init((QFsm*)&LEDDisplay, (QEvent*)0);
                            break;
                    
        case LDD_LEDOFF:    LEDDisplayEvt.dEvent.sig = LDD_LEDOFF;
                            QFsm_dispatch((QFsm*)&LEDDisplay, (QEvent*)&LEDDisplayEvt);
                            break;
                            
        case LDD_LEDON:     LEDDisplayEvt.dEvent.sig = LDD_LEDON;
                            QFsm_dispatch((QFsm*)&LEDDisplay, (QEvent*)&LEDDisplayEvt);
                            break;
                            
        case LDD_NEWVAL:    Double_dabble(&LEDDisplay, e.par);
                            break;
                            
        case LDD_TICK:      LEDDisplayEvt.dEvent.sig = LDD_TICK;
                            QFsm_dispatch((QFsm*)&LEDDisplay, (QEvent*)&LEDDisplayEvt);
                            break; 
                           
        default:            LEDDisplayEvt.dEvent.sig = LDD_LEDOFF;
                            QFsm_dispatch((QFsm*)&LEDDisplay, (QEvent*)&LEDDisplayEvt);
                            break;
    }
    return;
 }

/**==========================================================================**/
/* Private functions */
static void DisplayCtor(DisplayDriver *me)
{
    QFsm_ctor(&me->state, (QStateHandler)&DisplayInit);/* superclass ctor */
    return;
}

static QState DisplayInit(DisplayDriver *me, QEvent const *e)
{
    (void)e;
    me->DarkTime = DARK_TIMEOUT;
    return Q_TRAN(&DisplaySegOnes);
}

static QState DisplaySegOnes(DisplayDriver *me, QEvent const *e)
{
    switch (e->sig)
    {
        case Q_ENTRY_SIG:
            {
                #ifdef MYDEBUG
                    strcpy(DebugInfoStringLDD, SegOnesEnterString);
                #endif
                (void)LDD_Char2SegmentConvert(((DisplayDriver*)me)->digitvalue.ones);
                LEDDAnodeOnes();

                return Q_HANDLED();

            }
        case Q_EXIT_SIG:
            {
                #ifdef MYDEBUG
                    strcpy(DebugInfoStringLDD, SegOnesExitString);
                #endif
                LEDDLightOFF();
                while (me->DarkTime > 0)
                    --me->DarkTime;

                me->DarkTime = DARK_TIMEOUT;
                return Q_HANDLED();

            }
        case LDD_LEDOFF:
            {
                return Q_TRAN(&DisplayOFF);
            }
        case LDD_TICK:
            {
                return Q_TRAN(&DisplaySegTens);
            }
    }
    return Q_IGNORED();
}

/* Tens digit */
static QState DisplaySegTens(DisplayDriver *me, QEvent const *e)
{
    switch (e->sig)
    {
        case Q_ENTRY_SIG:
            {
                #ifdef MYDEBUG
                    strcpy(DebugInfoStringLDD, SegTensEnterString);
                #endif
                (void)LDD_Char2SegmentConvert(((DisplayDriver*)me)->digitvalue.tens);
                LEDDAnodeTens();

                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                #ifdef MYDEBUG
                    strcpy(DebugInfoStringLDD, SegTensExitString);
                #endif
                LEDDLightOFF();
                while (me->DarkTime > 0)
                    --me->DarkTime;

                me->DarkTime = DARK_TIMEOUT;
                return Q_HANDLED();

            }
        case LDD_LEDOFF:
            {
                return Q_TRAN(&DisplayOFF);
            }
        case LDD_TICK:
            {
                return Q_TRAN(&DisplaySegHundreds);
            }
    }
    return Q_IGNORED();
}

/* Hundreds digit */
static QState DisplaySegHundreds(DisplayDriver *me, QEvent const *e)
{
    switch (e->sig)
    {
        case Q_ENTRY_SIG:
            {
                #ifdef MYDEBUG
                    strcpy(DebugInfoStringLDD, SegHunsEnterString);
                #endif
                (void)LDD_Char2SegmentConvert(((DisplayDriver*)me)->digitvalue.hundreds);
                LEDDAnodeHundreds();

                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                #ifdef MYDEBUG
                    strcpy(DebugInfoStringLDD, SegHunsExitString);
                #endif
                LEDDLightOFF();
                while (me->DarkTime > 0)
                    --me->DarkTime;

                me->DarkTime = DARK_TIMEOUT;
                return Q_HANDLED();

            }
        case LDD_LEDOFF:
            {
                return Q_TRAN(&DisplayOFF);
            }
        case LDD_TICK:
            {
                return Q_TRAN(&DisplaySegThousands);
            }
    }
    return Q_IGNORED();
}

/* Thousand digit */
static QState DisplaySegThousands(DisplayDriver *me, QEvent const *e)
{
    switch (e->sig)
    {
        case Q_ENTRY_SIG:
            {
                #ifdef MYDEBUG
                    strcpy(DebugInfoStringLDD, SegThosEnterString);
                #endif
                (void)LDD_Char2SegmentConvert(((DisplayDriver*)me)->digitvalue.thousands);
                LEDDAnodeThousands();

                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                #ifdef MYDEBUG
                    strcpy(DebugInfoStringLDD, SegThosExitString);
                #endif
                LEDDLightOFF();
                while (me->DarkTime > 0)
                    --me->DarkTime;

                me->DarkTime = DARK_TIMEOUT;
                return Q_HANDLED();

            }
        case LDD_LEDOFF:
            {
                return Q_TRAN(&DisplayOFF);
            }
        case LDD_TICK:
            {
                return Q_TRAN(&DisplaySegOnes);
            }
    }
    return Q_IGNORED();
}

static QState DisplayOFF(DisplayDriver *me, QEvent const *e)
{
    switch (e->sig)
    {
        case Q_ENTRY_SIG:
            {
                LEDDLightOFF();
                return Q_HANDLED();
            }

        case LDD_LEDON:
            {
                return Q_TRAN(&DisplaySegOnes);
            }
    }
    return Q_IGNORED();

}

/**========================================================================================**/

/* Algorithm for BIN to BCD conversion */
static void Double_dabble(DisplayDriver *me, uint16_t binvalue)
{
    char scratch[6] = {0, 0, 0, 0, 0, 0};
    int j, k;
    int smin = NSCRATCH-2;    /* speed optimization */
    char *accessptr;

    accessptr = (char*)me;

    for (j = 0; j < 16; ++j)
        {
            /* This bit will be shifted in on the right. */
            int shifted_in = (binvalue & (1 << (15-j)))? 1: 0;

            /* Add 3 everywhere that scratch[k] >= 5. */
            for (k = smin; k < NSCRATCH; ++k)
              scratch[k] += (scratch[k] >= 5)? 3: 0;

            /* Shift scratch to the left by one position. */
            if (scratch[smin] >= 8)
              smin -= 1;
            for (k=smin; k < NSCRATCH-1; ++k) {
                scratch[k] <<= 1;
                scratch[k] &= 0xF;
                scratch[k] |= (scratch[k+1] >= 8);
            }

            /* Shift in the new bit from arr. */
            scratch[NSCRATCH-1] <<= 1;
            scratch[NSCRATCH-1] &= 0xF;
            scratch[NSCRATCH-1] |= shifted_in;
        }

    /* Certain output creating */
    for (k = 0; k < NSCRATCH; k++)
       *(accessptr + 3 + k) = scratch[4-k] + '0';

    return;
}

static LEDDD_State LDD_Char2SegmentConvert(char value)
{
    switch (value)
    {
        case '0':   LDD_SHOW_0();
                    return LEDDD_OK;
                    
        case '1':   LDD_SHOW_1();
                    return LEDDD_OK;
                    
        case '2':   LDD_SHOW_2();
                    return LEDDD_OK;
                    
        case '3':   LDD_SHOW_3();
                    return LEDDD_OK;
                    
        case '4':   LDD_SHOW_4();
                    return LEDDD_OK;
                    
        case '5':   LDD_SHOW_5();
                    return LEDDD_OK;
                    
        case '6':   LDD_SHOW_6();
                    return LEDDD_OK;
                    
        case '7':   LDD_SHOW_7();
                    return LEDDD_OK;
                    
        case '8':   LDD_SHOW_8();
                    return LEDDD_OK;
                    
        case '9':   LDD_SHOW_9();
                    return LEDDD_OK;
                    
        case 'E':   LDD_SHOW_E();
                    return LEDDD_OK;
                    
        case 'r':   LDD_SHOW_r();
                    return LEDDD_OK;
                    
        default:    LDD_SHOW_0();
                    return LEDD_FALSE;
    }
}


