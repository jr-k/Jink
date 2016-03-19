/*********************************************************************************************************
* 
* Edited by 		  : JRK (http://github.com/jreziga)
* Notice     		  : Wrapped Object Library of waveshare's epd library with editable serial pins
*
**********************************************************************************************************
* File                : epd.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.74
* Version             : V1.0
* By                  : V
*
*                                  (c) Copyright 2005-2014, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#include <Arduino.h>
#include "Jink.h"

Jink_ Jink;
SoftwareSerial* _serial;

Jink_::Jink_() {
	
}

Jink_::~Jink_() {	
}

void Jink_::begin(unsigned long baudr, uint8_t RX, uint8_t TX) {
	_serial = new SoftwareSerial(RX, TX); // RX, TX
    _serial->begin(baudr);
	pinMode(_wake_up, HIGH);
	pinMode(_reset, HIGH);
	defaultConfig();
}

void Jink_::end() {
    _serial->end();
}

void Jink_::defaultConfig(void)
{
	init();
	wakeup();
	setMemory(MEM_NAND);
	screenRotation(EPD_NORMAL);
}




/*******************************************************************************
* Function Name  : void reset(void)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::reset(void)
{
	digitalWrite(_reset, LOW);
	delayMicroseconds(10);
	digitalWrite(_reset, HIGH);
	delayMicroseconds(500);
	digitalWrite(_reset, LOW);
	delay(3000);
}
/*******************************************************************************
* Function Name  : void init(void)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::wakeup(void)
{
	digitalWrite(_wake_up, LOW);
	delayMicroseconds(10);
	digitalWrite(_wake_up, HIGH);
	delayMicroseconds(500);
	digitalWrite(_wake_up, LOW);
	delay(10);
}

/*******************************************************************************
* Function Name  : void handshake(void)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::handshake(void)
{
	memcpy(_cmd_buff, _cmd_handshake, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);
	
	_putchars(_cmd_buff, 9);
}
/*******************************************************************************
* Function Name  : void setBaud(long baud)
* Description    : set uart baud
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::setBaud(long baud)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0D;	
	
	_cmd_buff[3] = CMD_SET_BAUD;	
	
	_cmd_buff[4] = (baud >> 24) & 0xFF;
	_cmd_buff[5] = (baud >> 16) & 0xFF;
	_cmd_buff[6] = (baud >> 8) & 0xFF;
	_cmd_buff[7] = baud & 0xFF;
	
	_cmd_buff[8] = FRAME_E0;
	_cmd_buff[9] = FRAME_E1;
	_cmd_buff[10] = FRAME_E2;
	_cmd_buff[11] = FRAME_E3;	
	_cmd_buff[12] = _verify(_cmd_buff, 12);
	
	_putchars(_cmd_buff, 13);	
	
	delay(10);	
	// Serial.begin(baud);
	_serial->begin(baud);
}
/*******************************************************************************
* Function Name  : void readBaud(void)
* Description    : read uart baud
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::readBaud(void)
{
	memcpy(_cmd_buff, _cmd_read_baud, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);
	
	_putchars(_cmd_buff, 9);
}
/*******************************************************************************
* Function Name  : void setMemory(unsigned char mode)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::setMemory(unsigned char mode)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0A;	
	
	_cmd_buff[3] = CMD_MEMORYMODE;
	
	_cmd_buff[4] = mode;
	
	_cmd_buff[5] = FRAME_E0;
	_cmd_buff[6] = FRAME_E1;
	_cmd_buff[7] = FRAME_E2;
	_cmd_buff[8] = FRAME_E3;	
	_cmd_buff[9] = _verify(_cmd_buff, 9);
	
	_putchars(_cmd_buff, 10);		
}

/*******************************************************************************
* Function Name  : void enterStopmode(void)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::enterStopmode(void)
{
	memcpy(_cmd_buff, _cmd_stopmode, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);
	
	_putchars(_cmd_buff, 9);
}
/*******************************************************************************
* Function Name  : void udpate(void)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::udpate(void)
{
	memcpy(_cmd_buff, _cmd_update, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);
	
	_putchars(_cmd_buff, 9);
}
/*******************************************************************************
* Function Name  : void screenRotation(unsigned char mode)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::screenRotation(unsigned char mode)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0A;	
	
	_cmd_buff[3] = CMD_SCREEN_ROTATION;
	
	_cmd_buff[4] = mode;
	
	_cmd_buff[5] = FRAME_E0;
	_cmd_buff[6] = FRAME_E1;
	_cmd_buff[7] = FRAME_E2;
	_cmd_buff[8] = FRAME_E3;	
	_cmd_buff[9] = _verify(_cmd_buff, 9);
	
	_putchars(_cmd_buff, 10);	
}
/*******************************************************************************
* Function Name  : void loadFont(void)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::loadFont(void)
{
	memcpy(_cmd_buff, _cmd_load_font, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);
	
	_putchars(_cmd_buff, 9);	
}
/*******************************************************************************
* Function Name  : void loadPic(void)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::loadPic(void)
{
	memcpy(_cmd_buff, _cmd_load_pic, 8);
	_cmd_buff[8] = _verify(_cmd_buff, 8);
	
	_putchars(_cmd_buff, 9);
}
/*******************************************************************************
* Function Name  : void setColor(unsigned char color, unsigned char bkcolor)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::setColor(unsigned char color, unsigned char bkcolor)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0B;
	
	_cmd_buff[3] = CMD_SET_COLOR;
	
	_cmd_buff[4] = color;
	_cmd_buff[5] = bkcolor;
	
	_cmd_buff[6] = FRAME_E0;
	_cmd_buff[7] = FRAME_E1;
	_cmd_buff[8] = FRAME_E2;
	_cmd_buff[9] = FRAME_E3;
	_cmd_buff[10] = _verify(_cmd_buff, 10);
	
	_putchars(_cmd_buff, 11);
}
/*******************************************************************************
* Function Name  : void setEnglishFont(unsigned char font)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::setEnglishFont(unsigned char font)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0A;	
	
	_cmd_buff[3] = CMD_SET_EN_FONT;
	
	_cmd_buff[4] = font;
	
	_cmd_buff[5] = FRAME_E0;
	_cmd_buff[6] = FRAME_E1;
	_cmd_buff[7] = FRAME_E2;
	_cmd_buff[8] = FRAME_E3;	
	_cmd_buff[9] = _verify(_cmd_buff, 9);
	
	_putchars(_cmd_buff, 10);	
}
/*******************************************************************************
* Function Name  : void setChineseFont(unsigned char font)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::setChineseFont(unsigned char font)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0A;	
	
	_cmd_buff[3] = CMD_SET_CH_FONT;
	
	_cmd_buff[4] = font;
	
	_cmd_buff[5] = FRAME_E0;
	_cmd_buff[6] = FRAME_E1;
	_cmd_buff[7] = FRAME_E2;
	_cmd_buff[8] = FRAME_E3;	
	_cmd_buff[9] = _verify(_cmd_buff, 9);
	
	_putchars(_cmd_buff, 10);
}
/*******************************************************************************
* Function Name  : void drawPixel(int x0, int y0)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::drawPixel(int x0, int y0)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0D;	
	
	_cmd_buff[3] = CMD_DRAW_PIXEL;	
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	
	_cmd_buff[8] = FRAME_E0;
	_cmd_buff[9] = FRAME_E1;
	_cmd_buff[10] = FRAME_E2;
	_cmd_buff[11] = FRAME_E3;	
	_cmd_buff[12] = _verify(_cmd_buff, 12);
	
	_putchars(_cmd_buff, 13);
}
/*******************************************************************************
* Function Name  : void drawLine(int x0, int y0, int x1, int y1)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::drawLine(int x0, int y0, int x1, int y1)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x11;	
	
	_cmd_buff[3] = CMD_DRAW_LINE;	
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (x1 >> 8) & 0xFF;
	_cmd_buff[9] = x1 & 0xFF;
	_cmd_buff[10] = (y1 >> 8) & 0xFF;
	_cmd_buff[11] = y1 & 0xFF;	
	
	_cmd_buff[12] = FRAME_E0;
	_cmd_buff[13] = FRAME_E1;
	_cmd_buff[14] = FRAME_E2;
	_cmd_buff[15] = FRAME_E3;	
	_cmd_buff[16] = _verify(_cmd_buff, 16);
	
	_putchars(_cmd_buff, 17);	
}
/*******************************************************************************
* Function Name  : void fillRect(int x0, int y0, int x1, int y1)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::fillRect(int x0, int y0, int x1, int y1)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x11;	
	
	_cmd_buff[3] = CMD_FILL_RECT;	
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (x1 >> 8) & 0xFF;
	_cmd_buff[9] = x1 & 0xFF;
	_cmd_buff[10] = (y1 >> 8) & 0xFF;
	_cmd_buff[11] = y1 & 0xFF;	
	
	_cmd_buff[12] = FRAME_E0;
	_cmd_buff[13] = FRAME_E1;
	_cmd_buff[14] = FRAME_E2;
	_cmd_buff[15] = FRAME_E3;	
	_cmd_buff[16] = _verify(_cmd_buff, 16);
	
	_putchars(_cmd_buff, 17);		
}
/*******************************************************************************
* Function Name  : void drawCircle(int x0, int y0, int r)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::drawCircle(int x0, int y0, int r)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0F;	
	
	_cmd_buff[3] = CMD_DRAW_CIRCLE;	
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (r >> 8) & 0xFF;
	_cmd_buff[9] = r & 0xFF;
	
	
	_cmd_buff[10] = FRAME_E0;
	_cmd_buff[11] = FRAME_E1;
	_cmd_buff[12] = FRAME_E2;
	_cmd_buff[13] = FRAME_E3;	
	_cmd_buff[14] = _verify(_cmd_buff, 14);
	
	_putchars(_cmd_buff, 15);
}
/*******************************************************************************
* Function Name  : void fillCircle(int x0, int y0, int r)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::fillCircle(int x0, int y0, int r)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x0F;	
	
	_cmd_buff[3] = CMD_FILL_CIRCLE;	
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (r >> 8) & 0xFF;
	_cmd_buff[9] = r & 0xFF;
	
	
	_cmd_buff[10] = FRAME_E0;
	_cmd_buff[11] = FRAME_E1;
	_cmd_buff[12] = FRAME_E2;
	_cmd_buff[13] = FRAME_E3;	
	_cmd_buff[14] = _verify(_cmd_buff, 14);
	
	_putchars(_cmd_buff, 15);	
}
/*******************************************************************************
* Function Name  : void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x15;	
	
	_cmd_buff[3] = CMD_DRAW_TRIANGLE;	
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (x1 >> 8) & 0xFF;
	_cmd_buff[9] = x1 & 0xFF;
	_cmd_buff[10] = (y1 >> 8) & 0xFF;
	_cmd_buff[11] = y1 & 0xFF;	
	_cmd_buff[12] = (x2 >> 8) & 0xFF;
	_cmd_buff[13] = x2 & 0xFF;
	_cmd_buff[14] = (y2 >> 8) & 0xFF;
	_cmd_buff[15] = y2 & 0xFF;
	
	_cmd_buff[16] = FRAME_E0;
	_cmd_buff[17] = FRAME_E1;
	_cmd_buff[18] = FRAME_E2;
	_cmd_buff[19] = FRAME_E3;	
	_cmd_buff[20] = _verify(_cmd_buff, 20);
	
	_putchars(_cmd_buff, 21);		
}
/*******************************************************************************
* Function Name  : void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x15;	
	
	_cmd_buff[3] = CMD_FILL_TRIANGLE;	
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	_cmd_buff[8] = (x1 >> 8) & 0xFF;
	_cmd_buff[9] = x1 & 0xFF;
	_cmd_buff[10] = (y1 >> 8) & 0xFF;
	_cmd_buff[11] = y1 & 0xFF;	
	_cmd_buff[12] = (x2 >> 8) & 0xFF;
	_cmd_buff[13] = x2 & 0xFF;
	_cmd_buff[14] = (y2 >> 8) & 0xFF;
	_cmd_buff[15] = y2 & 0xFF;
	
	_cmd_buff[16] = FRAME_E0;
	_cmd_buff[17] = FRAME_E1;
	_cmd_buff[18] = FRAME_E2;
	_cmd_buff[19] = FRAME_E3;	
	_cmd_buff[20] = _verify(_cmd_buff, 20);
	
	_putchars(_cmd_buff, 21);	
}
/*******************************************************************************
* Function Name  : void clear(void)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::clear(void)
{
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = 0x00;
	_cmd_buff[2] = 0x09;	
	
	_cmd_buff[3] = CMD_CLEAR;
	
	_cmd_buff[4] = FRAME_E0;
	_cmd_buff[5] = FRAME_E1;
	_cmd_buff[6] = FRAME_E2;
	_cmd_buff[7] = FRAME_E3;	
	_cmd_buff[8] = _verify(_cmd_buff, 8);
	
	_putchars(_cmd_buff, 9);	
}

/*******************************************************************************
* Function Name  : void dispChar(unsigned char ch, int x0, int y0);
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::dispChar(unsigned char ch, int x0, int y0)
{
	unsigned char buff[2];
	
	buff[0] = ch;
	buff[1] = 0;
	
	dispString(buff, x0, y0);
}
/*******************************************************************************
* Function Name  : void dispString(const void * p, int x0, int y0)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::dispString(const void * p, int x0, int y0)
{
	int string_size;
	unsigned char * ptr = (unsigned char *)p;
	
	
	string_size = strlen((const char *)ptr);
	string_size += 14;
	
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = (string_size >> 8) & 0xFF;
	_cmd_buff[2] = string_size & 0xFF;
	
	_cmd_buff[3] = CMD_DRAW_STRING;
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	
	strcpy((char *)(&_cmd_buff[8]), (const char *)ptr);
	
	string_size -= 5;
	
	_cmd_buff[string_size] = FRAME_E0;
	_cmd_buff[string_size + 1] = FRAME_E1;
	_cmd_buff[string_size + 2] = FRAME_E2;
	_cmd_buff[string_size + 3] = FRAME_E3;
	_cmd_buff[string_size + 4] = _verify(_cmd_buff, string_size + 4);
	
	_putchars(_cmd_buff, string_size + 5);
}
/*******************************************************************************
* Function Name  : void dispBitmap(const void * p, int x0, int y0)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::dispBitmap(const void * p, int x0, int y0)
{
	int string_size;
	unsigned char * ptr = (unsigned char *)p;
	
	string_size = strlen((const char *)ptr);
	string_size += 14;
	
	_cmd_buff[0] = FRAME_B;
	
	_cmd_buff[1] = (string_size >> 8) & 0xFF;
	_cmd_buff[2] = string_size & 0xFF;
	
	_cmd_buff[3] = CMD_DRAW_BITMAP;
	
	_cmd_buff[4] = (x0 >> 8) & 0xFF;
	_cmd_buff[5] = x0 & 0xFF;
	_cmd_buff[6] = (y0 >> 8) & 0xFF;
	_cmd_buff[7] = y0 & 0xFF;
	
	strcpy((char *)(&_cmd_buff[8]), (const char *)ptr);
	
	string_size -= 5;
	
	_cmd_buff[string_size] = FRAME_E0;
	_cmd_buff[string_size + 1] = FRAME_E1;
	_cmd_buff[string_size + 2] = FRAME_E2;
	_cmd_buff[string_size + 3] = FRAME_E3;
	_cmd_buff[string_size + 4] = _verify(_cmd_buff, string_size + 4);
	
	_putchars(_cmd_buff, string_size + 5);	
}






/*******************************************************************************
* Function Name  : static void _putchars(const unsigned char * ptr, int n)
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		   : None
*******************************************************************************/
void Jink_::_putchars(unsigned char * ptr, int n)
{
	int i, x;
	
	for(i = 0; i < n; i++)
	{
	    x = ptr[i];
		// Serial.write(x);
		_serial->write(x);
	}
}
/*******************************************************************************
* Function Name  : static unsigned char _verify(const void * ptr, int n)
* Description    : 
* Input          : ptr      
                   n        
* Output         : None
* Return         : 
*******************************************************************************/
unsigned char Jink_::_verify(void * ptr, int n)
{
	int i;
	unsigned char * p = (unsigned char *)ptr;
	unsigned char result;
	
	for(i = 0, result = 0; i < n; i++)
	{
		result ^= p[i];
	}
	
	return result;
}








