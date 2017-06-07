// simpleLCD.c
/*
 * J.Piwowarczyk
 * materiały dydaktyczne
 * ver. 0.4
 */

#include"simpleLCD.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t liczbaLinii = 13;
static uint8_t numerLinii = 0;
static sFONT*  activeFont = &Font20;

void LCD_Init(void){
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER);
    BSP_LCD_SelectLayer(1);
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetFont(&Font20);
    liczbaLinii = 16; // dla Font20
    activeFont = &Font20;
}

void LCD_Clear(void){
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	numerLinii = 0;
}

void drawSquare(uint32_t x, uint32_t y, uint32_t size) {
	for( int i = x-size; i < x+size; i++)
		for( int j = y-size; j < y+size;j++)
		    BSP_LCD_DrawPixel(i, j, 0);
}

void LCD_SetFont(fontyTypeDef fon){
   switch(fon){
     case FONT8:
    	 activeFont = &Font8; //40
    	 break;
     case FONT12:
    	 activeFont = &Font12; //26
    	 break;
     case FONT16:
    	 activeFont = &Font16; //20
    	 break;
     case FONT20:
    	 activeFont = &Font20; //16
    	 break;
     case FONT24:
    	 activeFont = &Font24; //13
    	 break;
     default:
    	 activeFont = &Font20;
   }
   liczbaLinii = BSP_LCD_GetYSize()/activeFont->Height;
   BSP_LCD_SetFont(activeFont);
   BSP_LCD_Clear(LCD_COLOR_WHITE);
   numerLinii = 0;
}

void LCD_PrintLN(char* str){
  BSP_LCD_DisplayStringAtLine(numerLinii, (uint8_t*)str);
  numerLinii = (numerLinii + 1) % liczbaLinii;
}

void LCD_PrintCharXY(uint8_t x, uint8_t y, char ch){
  BSP_LCD_DisplayChar(x*activeFont->Width, y*activeFont->Height, (uint8_t)ch);
}

/*
 * LCD_PrintXY - funkcja
 * x - numer kolumny
 * y - numer linii
 *
 */
void LCD_PrintXY(uint8_t x, uint8_t y, char* str){
  BSP_LCD_DisplayStringAt(x*activeFont->Width, y*activeFont->Height, (uint8_t*)str, LEFT_MODE);
}

