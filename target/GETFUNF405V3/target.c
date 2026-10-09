/*
 * Timer map for GETFUNF405V3.
 * Motor output order matches the board's Betaflight numbering (resource dump),
 * so ESC wiring and motor numbering stay the same after migrating to INAV.
 */

#include <stdint.h>
#include <platform.h>

#include "drivers/io.h"
#include "drivers/timer.h"

timerHardware_t timerHardware[] = {
    DEF_TIM(TIM2, CH1, PA15, TIM_USE_OUTPUT_AUTO, 0, 0), // S1 - MOTOR 1
    DEF_TIM(TIM1, CH3, PA10, TIM_USE_OUTPUT_AUTO, 0, 1), // S2 - MOTOR 2
    DEF_TIM(TIM1, CH2, PA9,  TIM_USE_OUTPUT_AUTO, 0, 1), // S3 - MOTOR 3
    DEF_TIM(TIM1, CH1, PA8,  TIM_USE_OUTPUT_AUTO, 0, 1), // S4 - MOTOR 4
    DEF_TIM(TIM8, CH4, PC9,  TIM_USE_OUTPUT_AUTO, 0, 0), // S5 - MOTOR 5
    DEF_TIM(TIM8, CH3, PC8,  TIM_USE_OUTPUT_AUTO, 0, 1), // S6 - MOTOR 6
    DEF_TIM(TIM2, CH4, PB11, TIM_USE_OUTPUT_AUTO, 0, 0), // S7 - MOTOR 7
    DEF_TIM(TIM2, CH3, PB10, TIM_USE_OUTPUT_AUTO, 0, 0), // S8 - MOTOR 8

    DEF_TIM(TIM3, CH4, PB1,  TIM_USE_LED, 0, 0),         // WS2812 LED strip
};

const int timerHardwareCount = sizeof(timerHardware) / sizeof(timerHardware[0]);
