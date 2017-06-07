/* serial.c
 *
 * materiały dydaktyczne
 *
 * 2017 JP
 * ver. 0.1
 */

#include "stm32f429i_discovery.h"
#include "stm32f4xx_hal_uart.h"
#include "serial.h"

/* Private define ------------------------------------------------------------*/

// UART
/* Definition for UARTx clock resources */
#define UARTx                           UART5
#define UARTx_CLK_ENABLE()              __HAL_RCC_UART5_CLK_ENABLE()
#define UARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define UARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()

/* Definition for UARTx Pins */
#define UARTx_TX_PIN                    GPIO_PIN_12
#define UARTx_TX_GPIO_PORT              GPIOC
#define UARTx_TX_AF                     GPIO_AF8_UART5
#define UARTx_RX_PIN                    GPIO_PIN_2
#define UARTx_RX_GPIO_PORT              GPIOD
#define UARTx_RX_AF                     GPIO_AF8_UART5

/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

/* Function prototypes -----------------------------------------------*/
void Serial_Init(void);
void Serial_InitBaud(uint32_t BRate);

/* Private functions ---------------------------------------------------------*/

/*
 *  Inicjowanie UARTa
 *  TX : PC12
 *  RX : PD2
 *
 */
void Serial_Init(){
	Serial_InitBaud((uint32_t)9600);
}

void Serial_InitBaud(uint32_t BRate){
	  GPIO_InitTypeDef  GPIO_InitStruct;

	  /*##-1- Enable peripherals and GPIO Clocks #################################*/
	  /* Enable GPIO clock */
	  UARTx_TX_GPIO_CLK_ENABLE();
	  UARTx_RX_GPIO_CLK_ENABLE();

	  /* Enable USARTx clock */
	  UARTx_CLK_ENABLE();

	  /*##-2- Configure peripheral GPIO ##########################################*/
	  /* UART TX GPIO pin configuration  */
	  GPIO_InitStruct.Pin       = UARTx_TX_PIN;
	  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull      = GPIO_PULLUP;
	  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	  GPIO_InitStruct.Alternate = UARTx_TX_AF;

	  HAL_GPIO_Init(UARTx_TX_GPIO_PORT, &GPIO_InitStruct);

	  /* UART RX GPIO pin configuration  */
	  GPIO_InitStruct.Pin = UARTx_RX_PIN;
	  GPIO_InitStruct.Alternate = UARTx_RX_AF;

	  HAL_GPIO_Init(UARTx_RX_GPIO_PORT, &GPIO_InitStruct);

	  /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = none parity
	      - BaudRate    = eg. 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance          = UARTx;

	  UartHandle.Init.BaudRate     = BRate;//9600;
	  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits     = UART_STOPBITS_1;
	  UartHandle.Init.Parity       = UART_PARITY_NONE; // UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode         = UART_MODE_TX_RX;

	  if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    Error_Handler();
	  }

}

/*
 *  wysłanie danych bajtowych
 *  rozmiar = size
 */
void Serial_Send(uint8_t* str, uint16_t size){
	HAL_UART_Transmit(&UartHandle, (uint8_t*)str, size,1000);
}

/*
 *  odbiór danych
 *   do zapełnienia bufora
 *   lub do otrzymania znaku \r lub \n
 */

int16_t Serial_Receive(uint8_t* str, uint16_t size){
	uint32_t i=0;
	int8_t strIn[3]={0};
	uint32_t size0=(size>1)?size-1:1;
	for(i= 0; i<size;i++) str[i]=0;
	//while(__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE) == RESET );
	i=0;
	while(i<size0){
		if(HAL_UART_Receive(&UartHandle,(uint8_t*)strIn, 1,1000) == HAL_OK){
		  if(*strIn == '\r' || *strIn=='\n') break;
		  str[i]=*strIn;
		  i++;
		}
	}
    return (Serial_OK);
}

/*
 *  zwraca bez czekania odebrany jeden znak/bajt
 *  lub kod błędu : Serial_Error
 */

int16_t Serial_GetKey(){
	int8_t strIn[3];
	if(HAL_UART_Receive(&UartHandle,(uint8_t*)strIn, 1,10) == HAL_OK)
	  return (*strIn);
	return (Serial_Error);
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
