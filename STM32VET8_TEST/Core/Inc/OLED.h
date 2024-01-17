#ifndef __OLED_H
#define __OLED_H

#include "stm32f1xx.h"                  // Device header
#include <stdio.h>
void OLED_Init(void);
void OLED_ShowString(uint8_t x, uint8_t y, char *chr, uint8_t size);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_Fill(void);


#endif
