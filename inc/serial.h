/* serial.h
 *
 * materiały dydaktyczne
 *
 * 2017 JP
 * ver. 0.1
 */

#ifndef __SERIAL_H
#define __SERIAL_H

#define Serial_OK      0
#define Serial_Error ((int16_t)-1)

/* Function prototypes -----------------------------------------------*/
void Serial_Init(void);
void Serial_InitBaud(uint32_t BRate);

void Serial_Send(uint8_t* str, uint16_t size);
int16_t Serial_Receive(uint8_t* str, uint16_t size);
int16_t Serial_GetKey();

#endif //__SERIAL_H
