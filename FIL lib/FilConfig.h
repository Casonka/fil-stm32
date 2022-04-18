    /*!
    *   --------------------------------------------------------------------------
    *                ///Fast Initialization Library Configuration File\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin.
    *   @date 11/04/2022 - last update version FIL STM32
    *
    */

/*!
*   FIL STM32 Driver
*   @file <filConfig.h>
*   @note This file include driver Fast Initialization Library(FIL) for STM32 controllers
*/
#pragma once
#include <main.h>


#define _DefaultSectorIncludeHandler                0

#define _AdvancedSectorIncludeHandler               0
    #define _AdvancedCalculatingRCCIncluded         0
    #define _AdvancedGPIOIncluded                   0
    #define _AdvancedTimersIncluded                 0
    #define _AdvancedCalculatingTimersIncluded      0


/*!
*   Version control
*
*/
#if  !defined(STM32F40_41xxx) && !defined(STM32F401xx)
    #error Not supported on another devices
    #pragma message "Supported devices:"
    #pragma message "STM32F407VGT6, STM32F407VET6"
    #pragma message "STM32F401CCU6"
#endif /*Supporting device securing end*/

#if (_AdvancedSectorIncludeHandler == 1)
    #if (_AdvancedTimersIncluded == 1)
        #include "TIM.h"
    #endif



#endif


#define _DeveloperSectorIncludeHandler     0


