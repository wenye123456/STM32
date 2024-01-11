
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
	OLED_WriteCommand(0X8D); // ���õ�ɱ�
    OLED_WriteCommand(0X14); // ������ɱ�
    OLED_WriteCommand(0XAF); // OLED����

}

void OLED_OFF()
{
	OLED_WriteCommand(0X8D); // ���õ�ɱ�
    OLED_WriteCommand(0X10); // �رյ�ɱ�
    OLED_WriteCommand(0XAE); // OLED����
}
void OLED_Fill(void)
{
	
    for (uint8_t i = 0; i < 8; i++)
    {
        OLED_WriteCommand(0xb0 + i);  //����ҳ��ַ��0~7��
        OLED_WriteCommand(0x00);      //������ʾλ�á��е͵�ַ
        OLED_WriteCommand(0x10);      //������ʾλ�á��иߵ�ַ
        for (uint8_t n = 0; n < 128; n++)
            OLED_WriteData(0);   // Ҫ��������
    }
}


void OLED_Init()
{	

	HAL_Delay(300);  // ��Ҫ����Ҫɾ

    OLED_WriteCommand(0xAE); // OLED����
    OLED_WriteCommand(0x00); // ���õ��е�ַ
    OLED_WriteCommand(0x10); // ���ø��е�ַ
    OLED_WriteCommand(0x40); // ������ʼ��ַ��
    OLED_WriteCommand(0xB0); // set page address
    OLED_WriteCommand(0x81); // ���öԱȶ�
    OLED_WriteCommand(0x8F); // 128

    OLED_WriteCommand(0xA1); // 0xa0���ҷ��� 0xa1����
    OLED_WriteCommand(0xA6); // normal / reverse
    OLED_WriteCommand(0xA8); // ���ö�·����(1 to 64)
    OLED_WriteCommand(0x3F); // 1/32 duty
    OLED_WriteCommand(0xC8); // Com scan direction
    OLED_WriteCommand(0xD3); // ������ʾ��ƫ��ӳ���ڴ������
    OLED_WriteCommand(0x00); //

    OLED_WriteCommand(0xD5); // ������ʾʱ�ӷ�Ƶ��/����Ƶ��
    OLED_WriteCommand(0x80); // ���÷�Ƶ������ʱ������Ϊ100֡/��

    OLED_WriteCommand(0xD8); // set area color mode off
    OLED_WriteCommand(0x05); //

    OLED_WriteCommand(0xD9); // Ԥ���ʱ��
    OLED_WriteCommand(0xF1); // Ԥ���Ϊ15�����壬�ͷ�Ϊ1������

    OLED_WriteCommand(0xDA); // ��������Ӳ������
    OLED_WriteCommand(0x12); //

    OLED_WriteCommand(0xDB); // ����VCOM��ƽ
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

