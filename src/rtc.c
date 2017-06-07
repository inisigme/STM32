/* rtc.c
 *
 */

#include"stm32f429i_discovery.h"
#include"stm32f4xx_hal.h"

#include "stm32f4xx_hal_rtc.h"
#include"rtc.h"

RTC_HandleTypeDef hrtc;

extern void Error_Handler(void);

//void HAL_RNG_MspInit(RNG_HandleTypeDef* hrng){
//  if(hrng->Instance==RNG){
//    /* Peripheral clock enable */
//    __HAL_RCC_RNG_CLK_ENABLE();
//  }
//}

/* RTC init function */
void RTC_Init(void){

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

  __HAL_RCC_RTC_ENABLE();

    /**Initialize RTC Only
    */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK){
    Error_Handler();
  }

    /**Initialize RTC and set the Time and Date
    */
  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0) != 0x32F2){
    sTime.Hours = 0x8;
    sTime.Minutes = 0x02;
    sTime.Seconds = 0x0;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK){
      Error_Handler();
    }

    sDate.WeekDay = RTC_WEEKDAY_MONDAY;
    sDate.Month = RTC_MONTH_MAY;
    sDate.Date = 0x0a;
    sDate.Year = 17;

    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK){
      Error_Handler();
    }
    HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR0,0x32F2);
  }
}

void RTC_DeInit(){

  HAL_RTC_DeInit(&hrtc);
  if(hrtc.Instance==RTC){
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  }
}

void RTC_SetTime(RTC_TimeTypeDef sTime){

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK){
	    Error_Handler();
	}
}

void RTC_GetTime(RTC_TimeTypeDef *sTime){
	RTC_DateTypeDef sDate;
	if (HAL_RTC_GetTime(&hrtc, sTime, RTC_FORMAT_BIN)!= HAL_OK){
	    Error_Handler();
	  }
	if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN)!= HAL_OK){
	    Error_Handler();
	  }


}

void RTC_SetDate(RTC_DateTypeDef sDate){

	  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK){
	    Error_Handler();
	  }
}

void RTC_GetDate(RTC_DateTypeDef *sDate){
	RTC_TimeTypeDef sTime;

	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN)!= HAL_OK){
	    Error_Handler();
    }
	if (HAL_RTC_GetDate(&hrtc, sDate, RTC_FORMAT_BIN)!= HAL_OK){
	    Error_Handler();
    }
}

