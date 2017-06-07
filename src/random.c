/* random.c
 *
 * materiały dydaktyczne
 *
 * 2017 JP
 * ver. 0.1
 */

#include "stm32f429i_discovery.h"
#include "stm32f4xx_hal_rng.h"
#include "random.h"

/* Private variables ---------------------------------------------------------*/
static RNG_HandleTypeDef handleRNG;

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

void RNG_Init(void){
  /* RNG Peripheral clock enable */
  __HAL_RCC_RNG_CLK_ENABLE();

  handleRNG.Instance = RNG;
  if(HAL_RNG_Init(&handleRNG) != HAL_OK){
	Error_Handler();
  }
}

uint32_t RNG_Rand(void){
  uint32_t r = 0;
  r = HAL_RNG_GetRandomNumber(&handleRNG);
  return r;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void){
  /* Turn LED4 on */
  BSP_LED_On(LED4);
  while(1){
  }
}
