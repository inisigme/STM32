/* rtc.h
 *
 * materiały dydaktyczne
 *
 * 2017 JP
 * ver. 0.1
 */

#ifndef __RTC_H
#define __RTC_H

#include "stm32f4xx_hal_rtc.h"

void RTC_Init(void);
void RTC_SetTime(RTC_TimeTypeDef sTime);
void RTC_GetTime(RTC_TimeTypeDef *sTime);
void RTC_SetDate(RTC_DateTypeDef sDate);
void RTC_GetDate(RTC_DateTypeDef *sDate);

#endif //RTC.H
