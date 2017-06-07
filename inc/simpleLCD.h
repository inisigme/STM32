// simpleLCD.h
/*
 * J.Piwowarczyk
 * materiały dydaktyczne
 *
 */

#ifndef __SIMPLELCD_H
#define __SIMPLELCD_H

#include<stdio.h>
#include<stdlib.h>
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include"stm32f429i_discovery_lcd.h"

typedef enum{
	FONT8=8,
	FONT12=12,
	FONT16=16,
	FONT20=20,
	FONT24=24
} fontyTypeDef;

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetFont(fontyTypeDef fon);
void LCD_PrintLN(char* str);
void LCD_PrintCharXY(uint8_t x, uint8_t y, char ch);
void LCD_PrintXY(uint8_t x, uint8_t y, char* str);
void drawSquare(uint32_t, uint32_t, uint32_t);
#endif //__SIMPLELCD_H
