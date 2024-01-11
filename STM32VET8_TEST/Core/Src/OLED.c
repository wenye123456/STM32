
#include "OLED_Font.h"
#include "OLED.h"
#include "i2c.h"


void OLED_WriteCommand(uint8_t Command)
{
	HAL_I2C_Mem_Write(&hi2c1,0x78,0x00,I2C_MEMADD_SIZE_8BIT,&Command,1,100);
	
}

void OLED_WriteData(uint8_t Data)
{
	HAL_I2C_Mem_Write(&hi2c1,0x78,0x40,I2C_MEMADD_SIZE_8BIT,&Data,1,100);
}

void OLED_ON()
{
	OLED_WriteCommand(0X8D); // 设置电荷泵
    OLED_WriteCommand(0X14); // 开启电荷泵
    OLED_WriteCommand(0XAF); // OLED唤醒

}

void OLED_OFF()
{
	OLED_WriteCommand(0X8D); // 设置电荷泵
    OLED_WriteCommand(0X10); // 关闭电荷泵
    OLED_WriteCommand(0XAE); // OLED休眠
}
void OLED_Fill(void)
{
	
    for (uint8_t i = 0; i < 8; i++)
    {
        OLED_WriteCommand(0xb0 + i);  //设置页地址（0~7）
        OLED_WriteCommand(0x00);      //设置显示位置—列低地址
        OLED_WriteCommand(0x10);      //设置显示位置—列高地址
        for (uint8_t n = 0; n < 128; n++)
            OLED_WriteData(0);   // 要填充的数据
    }
}


void OLED_Init()
{	

	HAL_Delay(300);  // 重要，不要删

    OLED_WriteCommand(0xAE); // OLED休眠
    OLED_WriteCommand(0x00); // 设置低列地址
    OLED_WriteCommand(0x10); // 设置高列地址
    OLED_WriteCommand(0x40); // 设置起始地址线
    OLED_WriteCommand(0xB0); // set page address
    OLED_WriteCommand(0x81); // 设置对比度
    OLED_WriteCommand(0x8F); // 128

    OLED_WriteCommand(0xA1); // 0xa0左右反置 0xa1正常
    OLED_WriteCommand(0xA6); // normal / reverse
    OLED_WriteCommand(0xA8); // 设置多路复用(1 to 64)
    OLED_WriteCommand(0x3F); // 1/32 duty
    OLED_WriteCommand(0xC8); // Com scan direction
    OLED_WriteCommand(0xD3); // 设置显示的偏移映射内存计数器
    OLED_WriteCommand(0x00); //

    OLED_WriteCommand(0xD5); // 设置显示时钟分频比/振荡器频率
    OLED_WriteCommand(0x80); // 设置分频比例，时钟设置为100帧/秒

    OLED_WriteCommand(0xD8); // set area color mode off
    OLED_WriteCommand(0x05); //

    OLED_WriteCommand(0xD9); // 预充电时间
    OLED_WriteCommand(0xF1); // 预充电为15个脉冲，释放为1个脉冲

    OLED_WriteCommand(0xDA); // 引脚设置硬件配置
    OLED_WriteCommand(0x12); //

    OLED_WriteCommand(0xDB); // 设置VCOM电平
    OLED_WriteCommand(0x30); //
	OLED_ON();
	OLED_Fill();
}



void OLED_SetPos(uint8_t x, uint8_t y)
{
    OLED_WriteCommand(0xb0 + y);
    OLED_WriteCommand(((x & 0xf0) >> 4) | 0x10);
    OLED_WriteCommand((x & 0x0f));
}
void OLED_ShowString(uint8_t x, uint8_t y, char *chr, uint8_t size)
{
    uint8_t i = 0;
    uint8_t c = 0;

    if (size == 16)
    {
        while (chr[i] != '\0')
        {
            c = chr[i++] - ' ';
            OLED_SetPos(x, y);
            for (uint8_t j = 0; j < 8; j++)
                OLED_WriteData(F8X16[c * 16 + j]);
            OLED_SetPos(x, y + 1);
            for (uint8_t j = 0; j < 8; j++)
                OLED_WriteData(F8X16[c * 16 + j + 8]);

            x += 8;
            if (x > 120)
            {
                x = 0;
                y += 2;
            }
        }
    }
    else
    {
        while (chr[i] != '\0')
        {
            c = chr[i++] - ' ';
            OLED_SetPos(x, y);
            for (uint8_t j = 0; j < 6; j++)
                OLED_WriteData(F6x8[c][j]);

            x += 8;
            if (x > 120)
            {
                x = 0;
                y += 1;
            }
        }
    }
}

