/* 
 * File:   LEDDisplay_Driver.h
 * Author: martisek
 *
 * Created on 9. kv?tna 2017, 9:13
 */

#ifndef LEDDISPLAY_DRIVER_H
#define	LEDDISPLAY_DRIVER_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include "FSM.h"
#include "sst_port.h"
#include "Global_Task_def.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    
    #define DARK_TIMEOUT    30
    #define NSCRATCH        5

    #define LDD_SIG_OFFSET  Q_USER_SIG + 6


    /* Constants for GPIO ports manipulation */

    #define LDD_MASK_0_PC   ~0x000E
    #define LDD_MASK_1_PC   ~0x0004
    #define LDD_MASK_2_PC   ~0x001A
    #define LDD_MASK_3_PC   ~0x001E
    #define LDD_MASK_4_PC   ~0x0014
    #define LDD_MASK_5_PC   ~0x001E
    #define LDD_MASK_6_PC   ~0x001E
    #define LDD_MASK_7_PC   ~0x0006
    #define LDD_MASK_8_PC   ~0x001E
    #define LDD_MASK_9_PC   ~0x0016
    #define LDD_MASK_E_PC   ~0x001A
    #define LDD_MASK_r_PC   ~0x0010

    #define LDD_MASK_0_PA   ~0x010C
    #define LDD_MASK_1_PA   ~0x0008
    #define LDD_MASK_2_PA   ~0x0108
    #define LDD_MASK_3_PA   ~0x0008
    #define LDD_MASK_4_PA   ~0x000C
    #define LDD_MASK_5_PA   ~0x0004
    #define LDD_MASK_6_PA   ~0x0104
    #define LDD_MASK_7_PA   ~0x0008
    #define LDD_MASK_8_PA   ~0x010C
    #define LDD_MASK_9_PA   ~0x000C
    #define LDD_MASK_E_PA   ~0x0104
    #define LDD_MASK_r_PA   ~0x0100

    #define LDD_MASK_DARK_PC ~0xFFC1
    #define LDD_MASK_DARK_PA ~0xFE73
    #define LDD_MASK_DARK_PB ~0x57FF

    /*========================================================================*/
    /* Data types */
    typedef enum LEDDD_State LEDDD_State;
    typedef struct DisplayDigit DisplayDigit;
    typedef struct DisplayDriver DisplayDriver;
    typedef struct DisplayEvent DisplayEvent;
    typedef struct DisplayDigitValue DisplayDigitValue;
    typedef enum DisplaySignal DisplaySignal;
    
   
    struct DisplayDigitValue
    {
        char ones;
        char tens;
        char hundreds;
        char thousands;
    };

    /*
     struct DisplayDigitValue
    {
        char thousands;
        char hundreds;
        char tens;
        char ones;
    };
    */
    
    struct DisplayDriver
    {
        QFsm state;
        uint8_t DarkTime;
        DisplayDigitValue digitvalue;

    };

    struct DisplayEvent
    {
        QEvent dEvent;
        void *ptr;
    };

    enum DisplaySignal
    {
        LDD_INIT    = LDD_SIG_OFFSET + 0,   // 10
        LDD_TICK    = LDD_SIG_OFFSET + 1,   // 11
        LDD_LEDOFF  = LDD_SIG_OFFSET + 2,   // 12
        LDD_LEDON   = LDD_SIG_OFFSET + 3,   // 13
        LDD_NEWVAL  = LDD_SIG_OFFSET + 4    // 14
    };
    
    enum LEDDD_State
    {
        LEDDD_OK = 0,
        LEDD_FALSE = -1
    };
    
    /*========================================================================*/
    /* Function-like macros */
    
    #define LDD_SHOW_0()    do {\
                                PORTC = PORTC & LDD_MASK_0_PC;\
                                PORTA = PORTA & LDD_MASK_0_PA;\
                            } while (0)

    #define LDD_SHOW_1()    do {\
                                PORTC = PORTC & LDD_MASK_1_PC;\
                                PORTA = PORTA & LDD_MASK_1_PA;\
                            } while (0)

    #define LDD_SHOW_2()    do {\
                                PORTC = PORTC & LDD_MASK_2_PC;\
                                PORTA = PORTA & LDD_MASK_2_PA;\
                            } while (0)

    #define LDD_SHOW_3()    do {\
                                PORTC = PORTC & LDD_MASK_3_PC;\
                                PORTA = PORTA & LDD_MASK_3_PA;\
                            } while (0)

    #define LDD_SHOW_4()    if (1) {\
                                PORTC = PORTC & LDD_MASK_4_PC;\
                                PORTA = PORTA & LDD_MASK_4_PA;\
                            } else ((void)0)

    #define LDD_SHOW_5()    if (1) {\
                                PORTC = PORTC & LDD_MASK_5_PC;\
                                PORTA = PORTA & LDD_MASK_5_PA;\
                            } else ((void)0)

    #define LDD_SHOW_6()    if (1) {\
                                PORTC = PORTC & LDD_MASK_6_PC;\
                                PORTA = PORTA & LDD_MASK_6_PA;\
                            } else ((void)0)

    #define LDD_SHOW_7()    if (1) {\
                                PORTC = PORTC & LDD_MASK_7_PC;\
                                PORTA = PORTA & LDD_MASK_7_PA;\
                            } else ((void)0)

    #define LDD_SHOW_8()    if (1) {\
                                PORTC = PORTC & LDD_MASK_8_PC;\
                                PORTA = PORTA & LDD_MASK_8_PA;\
                            } else ((void)0)

    #define LDD_SHOW_9()    if (1) {\
                                PORTC = PORTC & LDD_MASK_9_PC;\
                                PORTA = PORTA & LDD_MASK_9_PA;\
                            } else ((void)0)

    #define LDD_SHOW_E()    if (1) {\
                                PORTC = PORTC & LDD_MASK_E_PC;\
                                PORTA = PORTA & LDD_MASK_E_PA;\
                            } else ((void)0)

    #define LDD_SHOW_r()    if (1) {\
                                PORTC = PORTC & LDD_MASK_r_PC;\
                                PORTA = PORTA & LDD_MASK_r_PA;\
                            } else ((void)0)
    
    
    #define LEDDLightOFF()  if (1) {\
                                PORTC = LATC | LDD_MASK_DARK_PC;\
                                PORTA = LATA | LDD_MASK_DARK_PA;\
                                PORTB = LATB | LDD_MASK_DARK_PB;\
                             } else ((void)0)

    #define LEDDAnodeOnes()     ((PORTBbits.RB15) = (unsigned)0)
    #define LEDDAnodeTens()     ((PORTAbits.RA7)  = (unsigned)0)
    #define LEDDAnodeHundreds() ((PORTBbits.RB13) = (unsigned)0)
    #define LEDDAnodeThousands()((PORTBbits.RB11) = (unsigned)0)

   
    /*========================================================================*/
    /* Function prototypes */
    void SST_TaskLDD(SSTEvent e);


#ifdef	__cplusplus
}
#endif

#endif	/* LEDDISPLAY_DRIVER_H */

