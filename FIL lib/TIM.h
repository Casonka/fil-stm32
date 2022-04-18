    /*!
    *   --------------------------------------------------------------------------
    *                       ///TIM initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 11/04/2022 - last update version TIM
    *
    *       @note This file for configuration main functional properties of timers
    */
#pragma once
#include "FilConfig.h"

    /*!
    *   @brief TimPWMConfigure(TIM,prescaler,autoreset,ch1,ch2,ch3,ch4) - configuration timer in PWM mode
    *       @arg TIM - number of timer
    *       @arg prescaler - value for increase the input frequency
    *       @arg autoreset - value for set the period of timer
    *       @arg ch<n> - activate/deactivate the channels of timer
    */
    #define TimPWMConfigure(TIM,prescaler,autoreset,ch1,ch2,ch3,ch4) {\
        ConfChannelsTim(TIM,6,6,ch1,ch2,ch3,ch4);                    \
        ConfFreq(TIM,prescaler,autoreset);                           \
        TimStart(TIM);                                               \
        ConfTimMainOutput(TIM,1);                                    \
        ConfTimAutomaticOutput(TIM,1);                               \
        ResetTimCCR1(TIM);                                           \
        ResetTimCCR2(TIM);                                           }

    /*!
    *   @brief TimPIDConfigure(TIM,frequency) - configuration timer in calculating mode
    *   (P-regulation, PI - regulation, PID - regulation and other regulations)
    *       @arg TIM - number of timer
    *       @arg freq - target frequency for calculating
    */
    #define TimPIDConfiqure(TIM,freq)       {\
        ResetTimCNT(TIM);                   \
        ConfPIDFreq(TIM,freq);              \
        ConfTimUpdatInterrupt(TIM,1);       \
        TimStart(TIM);                      }

    /*!
    *   @brief TimEncoderConfigure(TIM) - configuration timer with encoder interface
    *       @arg TIM - number of timer
    */
    #define TimEncoderConfiqure(TIM)    {\
        ResetTimPSC(TIM);               \
        ConfTimARR(TIM,0xFFFFFFFF);     \
        TimStart(TIM);                  \
        ConfSms(TIM,0x3);               \
        ConfEtf(TIM,0xF);               }

    /*!
    *   @brief TimPWMInputCaptureConfigure(TIM) - configuration timer for check length of PWM
    *       @arg TIM - number of timer
    */
    #define TimPWMInputCaptureConfiqure(TIM)                          {\
        ResetTimPSC(TIM);                                             \
        ConfTimARR(TIM,0xFFFFFFFF);                                  \
        ConfCaptureSelection1(TIM,0x1,0x2,1);                         \
        ConfCapturePolarity(TIM,0x0,0x1,0x0,0x1,1,0);                 \
        ConfCaptureComplementaryPolarity(TIM,0x0,0x1,0x0,0x1,1,0);    \
        ConfTriggerSelection(TIM,0x5);                                \
        ConfSms(TIM,0x4);                                             \
        ConfTimCapture(TIM,0x1,0x1,0,0,1,1,0,0);                      \
        TimStart(TIM);                                                }

    /*!
    *   @brief TimPWMCentralAlignedModeConfigure(TIM,prescaler,autoreset,ch1,ch2,polarity1,ch3,ch4,polarity2) - configuration timer with central aligned mode
    *       @arg TIM - number of timer
    *       @arg prescaler - value for increase the input frequency
    *       @arg autoreset - value for set the period of timer
    *       @arg polarity<n> - set polarity level for PWM output
    *       @arg ch<n> - activate/deactivate the channels of timer
    */
    #define TimPWMCentralAlignedModeConfigure(TIM,prescaler,autoreset,ch1,ch2,polarity1,ch3,ch4,polarity2) {\
        ConfChannelsTim(TIM,polarity1,polarity2,ch1,ch2,ch3,ch4);                                          \
        ConfFreq(TIM,prescaler,autoreset);                                                                 \
        TimStart(TIM);                                                                                     \
        ResetTimCCR1(TIM);                                                                                 \
        ResetTimCCR2(TIM);                                                                                 }

//----------------------------High commands------------------------------------//

    #define ConfChannelsTim(TIM,mode1,mode2,ch1,ch2,ch3,ch4,) {\
        ConfTimOutputCompare1(TIM,mode1,mode1,ch1,ch2);       \
        ConfTimOutputCompare2(TIM,mode2,mode2,ch3,ch4);       \
        ConfTimCompareFast1(TIM,1,1,ch1,ch2);                 \
        ConfTimCompareFast2(TIM,1,1,ch3,ch4);                 \
        ConfTimCapture(TIM,1,1,1,1,ch1,ch2,ch3,ch4);          }

    #define ConfPIDFreq(TIM,freq)           {\
        ConfTimPSC(TIM,psc_calc);           \
        ConfTimARR(TIM,calc_arr(freq));     }

    #define ConfFreq(TIM,prescaler,autoreset)   {\
        ConfTimPSC(TIM,prescaler);              \
        ConfTimARR(TIM,autoreset);              }

    #define ConfTimStart(TIM)           {\
        ConfTimCounter(TIM,0x1);        \
        ConfTimPreloadARR(TIM,0x1);     }

    #define ConfTimCCR(TIM,duty1,duty2,duty3,duty4)
//-----------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
    #define ConfTimPSC(TIM,PSC)           {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x28)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x28))&(~tim_psc(0xFFFF)))|tim_psc(PSC));}

    #define ConfTimARR(TIM,ARR)           {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x2C)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x2C))|(~tim_arr(0x00000000)))&tim_arr(ARR));}

    #define ConfTimCounter(TIM,cen)       {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x00)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x00))&(~tim_counter(0x1)))|tim_counter(cen));}

    #define ConfTimPreloadARR(TIM,arpe)  {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x00)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x00))&(~tim_preload_arr(0x1)))|tim_preload_arr(arpe));}

    #define ConfTimUpdateRequest(TIM,urs)  {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x00)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x00))&(~tim_update_request(0x1)))|tim_psc(urs));}

    #define ConfTimOutputCompare1(TIM,oc1m,oc2m,ch1,ch2)         {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x18)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x18))&(~tim_output_compare1(0x7,0x7,1,1)))|tim_output_compare1(oc1m,oc2m,ch1,ch2));}

    #define ConfTimOutputCompare2(TIM,oc3m,oc4m,ch3,ch4)         {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x1C)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x1C))&(~tim_output_compare2(0x7,0x7,1,1)))|tim_output_compare2(oc3m,oc4m,ch3,ch4));}

    #define ConfTimCompareFast1(TIM,oc1fe,oc2fe,ch1,ch2)         {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x18)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x18))&(~tim_output_compare_fast1(0x1,0x1,1,1)))|tim_output_compare_fast1(oc1fe,oc2fe,ch1,ch2));}

    #define ConfTimCompareFast2(TIM,oc3fe,oc4fe,ch3,ch4)         {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x1C)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x1C))&(~tim_output_compare_fast2(0x1,0x1,1,1)))|tim_output_compare_fast2(oc3fe,oc4fe,ch3,ch4));}

    #define ConfTimCapture(TIM,cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4) {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x20)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x20))&(~tim_capture(0x1,0x1,0x1,0x1,1,1,1,1)))|tim_capture(cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4));}

    #define ConfTimUpdateInterrupt(TIM,uie)  {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x0C)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x0C))&(~tim_update_interrupt(0x1)))|tim_update_interrupt(uie));}

    #define ConfTimMainOutput(TIM,moe)  {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x44)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x44))&(~tim_main_output(0x1)))|tim_main_output(moe));}

    #define ConfTimAutomaticOutput(TIM,aoe)  {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x44)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x44))&(~tim_automatic_output(0x1)))|tim_automatic_output(aoe));}

    #define ConfTimUpdateGeneration(TIM,ug)  {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x14)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x14))&(~tim_update_generation(0x1)))|tim_update_generation(ug));}

    #define ConfCCR1(TIM,value)         {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x34)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x34))&(~tim_ccr1(0xFFFF)))|tim_ccr1(value));}

    #define ConfCCR2(TIM,value)         {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x38)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x38))&(~tim_ccr2(0xFFFF)))|tim_ccr2(value));}

    #define ConfCCR3(TIM,value)         {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x3C)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x3C))&(~tim_ccr3(0xFFFF)))|tim_ccr3(value));}

    #define ConfCCR4(TIM,value)         {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x40)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x40))&(~tim_ccr4(0xFFFF)))|tim_ccr4(value));}

    #define ConfSMS(TIM,sms)            {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x08)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x08))&(~tim_sms(0xF)))|tim_sms(sms));}

    #define ConfEtf(TIM,etf)            {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x08)) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x08))&(~tim_etf(0x7)))|tim_etf(etf));}

    #define ConfCaptureSelection1(TIM,cc1s,cc2s,ch1)   {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x18)) = \
                                                       ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x18))&(~tim_capture_selection1(0x3,0x3,1)))|tim_capture_selection1(cc1s,cc2s,ch1));}

    #define ConfCaptureSelection2(TIM,cc3s,cc4s,ch2)   {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x1C)) = \
                                                       ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x1C))&(~tim_capture_selection2(0x3,0x3,1)))|tim_capture_selection2(cc3s,cc4s,ch2));}

    #define ConfCapturePolarity(TIM,cc1p,cc2p,cc3p,cc4p,ch1,ch2)  {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x20)) = \
                                                                  ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x20))&(~tim_capture_polarity(0x1,0x1,0x1,0x1,1,1)))|tim_capture_polarity(cc1p,cc2p,cc3p,cc4p,ch1,ch2));}

    #define ConfCaptureComplementaryPolarity(TIM,cc1np,cc2np,cc3np,cc4np,ch1,ch2)    {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x20)) = \
                                                                                     ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x20))&(~tim_capture_complementary_polarity(0x1,0x1,0x1,0x1,1,1)))|tim_capture_complementary_polarity(cc1np,cc2np,cc3np,cc4np,ch1,ch2));}

    #define ConfTriggerSelection(TIM,ts)  {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x08)) = \
                                          ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM) + 0x08))&(~tim_trigger_selection(0x7)))|tim_trigger_selection(ts));}

    #define ConfOnePulseMode(TIM,opm)   {* ((uint32_t *)(tim_base(TIM) + tim_id(TIM))) = \
                                        ((* ((uint32_t *)(tim_base(TIM) + tim_id(TIM)))&(~tim_opm(0x1)))|tim_opm(opm));}
//----------------------------Calculating-------------------------------------//
    #define CalcPSC(freq)      ((uint16_t)((current_systick/(freq*MAX_PWM))))
    #define CalcARR(freq)      ((uint16_t)(current_systick/freq*(psc_calc)))

//----------------------------Macro numbers of timers------------------------//
    #define Tim1  16
    #define Tim2  0
    #define Tim3  1
    #define Tim4  2
    #define Tim5  3
    #define Tim6  4
    #define Tim7  5
    #define Tim8  17
    #define Tim9  32
    #define Tim10 33
    #define Tim11 34
    #define Tim12 6
    #define Tim13 7
    #define Tim14 8
    #define RTC   10
//---------------------------Calculating address number of timer----------------------------------------//
    #define TimOffset      ((uint32_t)0x00400)
    #define TimBase(TIM)   (PERIPH_BASE +(0x00010000 * ((TIM&0x10)>>4)) + (0x00014000 * ((TIM&0x20)>>5)))
    #define TimID(TIM)     ((uint32_t)((TIM&0xF)*tim_offset))
//------------------------------Registers of timers----------------------------------------------------------------------------------------------------------------------------------//
    #define tim_cnt(cnt)                                            ((uint16_t)(cnt))
    #define tim_counter(cen)                                        ((uint16_t)(cen))
    #define tim_preload_arr(arpe)                                   ((uint16_t)((arpe) << 7))
    #define tim_update_request(urs)                                 ((uint16_t)((urs) << 2))
    #define tim_psc(psc)                                            ((uint16_t)(psc))
    #define tim_arr(arr)                                            ((uint32_t)(arr))
    #define tim_output_compare1(oc1m,oc2m,ch1,ch2)                  ((uint16_t)((((oc2m) << 12)*ch2) | (((oc1m) << 4)*ch1)))
    #define tim_output_compare2(oc3m,oc4m,ch3,ch4)                  ((uint16_t)((((oc4m) << 12)*ch4) | (((oc3m) << 4)*ch3)))
    #define tim_output_compare_fast1(oc1fe,oc2fe,ch1,ch2)           ((uint16_t)((((oc2fe) << 10)*ch2) | (((oc1fe) << 2)*ch1)))
    #define tim_output_compare_fast2(oc3fe,oc4fe,ch3,ch4)           ((uint16_t)((((oc4fe) << 10)*ch4) | (((oc3fe) << 2)*ch3)))
    #define tim_capture(cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4)        ((uint16_t)((((cc4e) << 12)*ch4) | (((cc3e) << 8)*ch3)| (((cc2e) << 4)*ch2) | ((cc1e)*ch1)))
    #define tim_capture_selection1(cc1s,cc2s,ch1)                   ((uint16_t)((((cc2s) << 8)*ch1) | ((cc1s)*ch1)))
    #define tim_capture_selection2(cc3s,cc4s,ch2)                   ((uint16_t)((((cc4s) << 8)*ch2) | ((cc3s)*ch2)))
    #define tim_update_interrupt(uie)                               ((uint16_t)(uie))
    #define tim_main_output(moe)                                    ((uint16_t)((moe) << 15))
    #define tim_automatic_output(aoe)                               ((uint16_t)((aoe) << 14))
    #define tim_update_generation(ug)                               ((uint16_t)(ug))
    #define tim_ccr1(value)                                         ((uint16_t)(value))
    #define tim_ccr2(value)                                         ((uint16_t)(value))
    #define tim_ccr3(value)                                         ((uint16_t)(value))
    #define tim_ccr4(value)                                         ((uint16_t)(value))
    #define tim_sms(sms)                                            ((uint16_t)(sms))
    #define tim_etf(etf)                                            ((uint16_t)((etf) << 8))
    #define tim_capture_polarity(cc1p,cc2p,cc3p,cc4p,ch1,ch2)       ((uint16_t)((((cc4p) << 13)*ch2) | (((cc3p) << 9)*ch2)| (((cc2p) << 5)*ch1) | (((cc1p) << 1)*ch1)))
    #define tim_capture_complementary_polarity(cc1np,cc2np,cc3np,cc4np,ch1,ch2) ((uint16_t)((((cc4np) << 15)*ch2) | (((cc3np) << 11)*ch2)| (((cc2np) << 7)*ch1) | (((cc1np) << 3)*ch1)))
    #define tim_trigger_selection(ts)                               ((uint16_t)((ts) << 4))
    #define tim_sr(sr)                                              ((uint16_t)(sr))
    #define tim_opm(opm)                                            ((uint16_t)(opm) << 3)

//---------------------------------------Calculating address and reset state---------------------------------------------------//
    #define reset_tim_cnt(TIM)      (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x24) &= (~tim_cnt(0xFFFF)))
    #define reset_tim_psc(TIM)      (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x28) &= (~tim_psc(0xFFFF)))
    #define reset_tim_arr(TIM)      (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x2C) |= (~tim_arr(0x0000)))
    #define reset_tim_ccr1(TIM)     (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x34) &= (~tim_ccr1(0xFFFF)))
    #define reset_tim_ccr2(TIM)     (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x38) &= (~tim_ccr2(0xFFFF)))
    #define reset_tim_ccr3(TIM)     (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x3C) &= (~tim_ccr3(0xFFFF)))
    #define reset_tim_ccr4(TIM)     (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x40) &= (~tim_ccr4(0xFFFF)))
    #define reset_tim_sr(TIM)       (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x10) &= (~tim_sr(0xFFFF)))

//----------------------------------------Calculating address and get state----------------------------------------------------//
    #define get_cnt(TIM) ((uint32_t)(* (uint32_t *)(tim_base(TIM)+tim_id(TIM)+0x24)))
    #define get_arr(TIM) ((uint32_t)(* (uint32_t *)(tim_base(TIM)+tim_id(TIM)+0x2C)))

//----------------------------------------Calculating address and set state-----------------------------------------------------------------------------------------------------------------------------------//
    #define set_tim_counter(TIM,cen)                        (* (uint32_t *)((tim_base(TIM) + tim_id(TIM))) |= tim_counter(cen))
    #define set_tim_preload_arr(TIM,arpe)                   (* (uint32_t *)((tim_base(TIM) + tim_id(TIM))) |= tim_preload_arr(arpe))
    #define set_tim_update_request(TIM,urs)                 (* (uint32_t *)((tim_base(TIM) + tim_id(TIM))) |= tim_update_request(urs))
    #define set_OnePulseMode(TIM,opm)                       (* (uint32_t *)((tim_base(TIM) + tim_id(TIM))) |= tim_opm(opm))
    #define set_tim_psc(TIM,PSC)                            (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x28) |= tim_psc(PSC))
    #define set_tim_arr(TIM,ARR)                            (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x2C) &= tim_arr(ARR))
    #define set_output_compare1(TIM,oc1m,oc2m,ch1,ch2)      (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x18) |= tim_output_compare1(oc1m,oc2m,ch1,ch2))
    #define set_output_compare2(TIM,oc3m,oc4m,ch3,ch4)      (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x1C) |= tim_output_compare1(oc3m,oc4m,ch3,ch4))
    #define set_compare_fast1(TIM,oc1fe,oc2fe,ch1,ch2)      (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x1C) |= tim_output_compare_fast1(oc1fe,oc2fe,ch1,ch2))
    #define set_compare_fast2(TIM,oc3fe,oc4fe,ch3,ch4)      (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x1C) |= tim_output_compare_fast2(oc3fe,oc4fe,ch3,ch4))
    #define set_capture(TIM,cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4)    (* (uint32_t *)((tim_base(TIM) + tim_id(TIM) + 0x20)) |= tim_capture(cc1e,cc2e,cc3e,cc4e,ch1,ch2,ch3,ch4))
    #define set_update_interrupt(TIM,uie)                    (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x0C) |= tim_update_interrupt(uie))
    #define set_main_output(TIM,moe)                         (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x44) |= tim_main_output(moe))
    #define set_automatic_output(TIM,aoe)                    (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x44) |= tim_automatic_output(aoe))
    #define set_update_generation(TIM,ug)                    (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x14) |= tim_update_generation(ug))
    #define set_ccr1(TIM,value)                              (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x34) |= tim_ccr1(value))
    #define set_ccr2(TIM,value)                              (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x38) |= tim_ccr2(value))
    #define set_ccr3(TIM,value)                              (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x3C) |= tim_ccr3(value))
    #define set_ccr4(TIM,value)                              (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x40) |= tim_ccr4(value))
    #define set_sms(TIM,sms)                                 (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x08) |= tim_sms(sms))
    #define set_etf(TIM,etf)                                 (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x08) |= tim_etf(etf))
    #define set_capture_selection1(TIM,cc1s,cc2s,ch1)        (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x18) |= tim_capture_selection1(cc1s,cc2s,ch1))
    #define set_capture_selection2(TIM,cc3s,cc4s,ch2)        (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x1C) |= tim_capture_selection1(cc3s,cc4s,ch2))
    #define set_capture_polarity(TIM,cc1p,cc2p,cc3p,cc4p,ch1,ch2)   (* (uint32_t *)((tim_base(TIM) + tim_id(TIM) + 0x20)) |= tim_capture(cc1p,cc2p,cc3p,cc4p,ch1,ch2))
    #define set_capture_complementary_polarity(TIM,cc1np,cc2np,cc3np,cc4np,ch1,ch2) (* (uint32_t *)((tim_base(TIM) + tim_id(TIM) + 0x20)) |= tim_capture_complementary_polarity(cc1np,cc2np,cc3np,cc4np,ch1,ch2))
    #define set_trigger_selection(TIM,ts)                    (* (uint32_t *)((tim_base(TIM) + tim_id(TIM)) + 0x08) |= tim_trigger_selection(ts))

