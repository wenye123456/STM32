#ifndef __OLED_H
#define __OLED_H

#include "stm32f1xx.h"                  // Device header
#include <stdio.h>
void OLED_Init(void);
void OLED_ShowString(uint8_t x, uint8_t y, char *chr, uint8_t size);
void OLED_Fill(void);


#endif
