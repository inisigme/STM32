/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Game.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "system_clocks.h"
#include "simpleLCD.h"
#include "random.h"
#include "serial.h"
#include "rtc.h"
#include "stm32f429i_discovery_gyroscope.h"
/* Private typedef -----------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Private macro -----------------------
 * --------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

//static RTC_TimeTypeDef sTime;
//static RTC_DateTypeDef sDate;

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

//static char str[30]={0};

/* Private function prototypes -----------------------------------------------*/
static void EXTILine0_Config(void);

/* Private functions ---------------------------------------------------------*/


int main(void){


  HAL_Init();

  /* Configure LED3 and LED4 */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
  EXTILine0_Config();

  BSP_LCD_Init();
  LCD_Init();
  Serial_Init();
   //Serial_Send((uint8_t*)"UART Start OK \n ", 15);
  LCD_SetFont(FONT16);
//  LCD_PrintXY(6,1,"Witamd t !");

  // --------------------
  // inicjowanie RTC zegara czasu rzeczywistego - kalendarza
  RTC_Init();
  //LCD_PrintXY(0,3,"RTC Init OK!!");
  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  BSP_GYRO_Init();
  /* Infinite loop */
  char bufor[5][50];
  float pfData[3];

  initState();

  while(1){
    BSP_LED_Toggle(LED3); //czyli PG13
    BSP_GYRO_GetXYZ(pfData);

    RNG_Init();
    sprintf(bufor[0], "%f", (float)RNG_Rand()/(float)UINT32_MAX);
    sprintf(bufor[1], "%f", (float)RNG_Rand()/(float)UINT32_MAX);
    sprintf(bufor[2], "%f", (float)RNG_Rand()/(float)UINT32_MAX);

    uint32_t X = BSP_LCD_GetXSize();
    uint32_t Y = BSP_LCD_GetYSize();

    sprintf(bufor[3], "%f", (float)RNG_Rand()/(float)UINT32_MAX);
    sprintf(bufor[4], "%f", (float)RNG_Rand()/(float)UINT32_MAX);

    updatePos(pfData);
    drawSquare(state.playerPosX, state.playerPosY, 10);
    int qwe;
    for(qwe = 0; qwe < state.size; qwe++) {
    	state.meteors[qwe][1] += state.offset/1000.0;
    }
    for(qwe = 0; qwe < state.size; qwe++) {
    		drawSquare(state.meteors[qwe][0],state.meteors[qwe][1],2);
   	}
	sprintf(bufor[0], "HP: %i", (int)state.hp);
	LCD_PrintXY(1,1, bufor[0]);
	sprintf(bufor[0], "Scores: %i", (int)state.offset );
	LCD_PrintXY(1,2, bufor[0]);

    for(qwe = 0; qwe < state.size; qwe++) {
    	if((abs(state.playerPosX - state.meteors[qwe][0]) <= 5) &&
    			(abs(state.playerPosY - state.meteors[qwe][1]) <= 5)) {
    		state.hp--;
    		state.meteors[qwe][1] = 3333.f;
    		state.meteors[qwe][0] = 3333.f;
    		if( state.hp < 0.1) {
    			LCD_Clear();
    			sprintf(bufor[0], "Koniec");
    			LCD_PrintXY(3,3, bufor[0]);
    			sprintf(bufor[0], "HP: %i", (int)state.hp);
    			LCD_PrintXY(1,7, bufor[0]);
    			sprintf(bufor[0], "Scores: %i", (int)state.offset );
    			LCD_PrintXY(3,8, bufor[0]);
    			initState();
    			HAL_Delay(22222);
    		}
    	}
    }
    state.offset += 5.f;
    HAL_Delay(50);//
    LCD_Clear();
  }
}

/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == KEY_BUTTON_PIN)
  {
	  state.locked = state.locked == 0 ? 1 : 0;
  }
}

/*
void HAL_SYSTICK_Callback(void)
{
  // tu wpisz obsługę SysTick
  // czyli co ma byc wykonywane co 1[ms]

}

*/

