/*********************************************************************************************************
* 
* Edited by 		  : JRK (http://github.com/jreziga)
* Notice     		  : Wrapped Object Library of waveshare's epd library with editable serial pins
*
**********************************************************************************************************
*									   Based on WaveShare "epd" library
*                                  (c) Copyright 2005-2014, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#ifndef JINK_H
#define JINK_H

#include <Arduino.h>
#include <SoftwareSerial.h>

/*
general
*/
#define    CMD_SIZE                           512	

/*
frame format
*/
#define    FRAME_B                            0xA5
#define    FRAME_E0                           0xCC
#define    FRAME_E1                           0x33
#define    FRAME_E2                           0xC3
#define    FRAME_E3                           0x3C

/*
color define
*/
#define    WHITE                              0x03
#define    GRAY                               0x02
#define    DARK_GRAY                          0x01
#define    BLACK                              0x00

/*
command define
*/
#define    CMD_HANDSHAKE                      0x00                                                     //handshake
#define    CMD_SET_BAUD                       0x01                                                     //set baud
#define    CMD_READ_BAUD                      0x02                                                     //read baud
#define    CMD_MEMORYMODE                     0x07                                                     //set memory mode
#define    CMD_STOPMODE                       0x08                                                     //enter stop mode 
#define    CMD_UPDATE                         0x0A                                                     //update
#define    CMD_SCREEN_ROTATION                0x0D                                                     //set screen rotation
#define    CMD_LOAD_FONT                      0x0E                                                     //load font
#define    CMD_LOAD_PIC                       0x0F                                                     //load picture

#define    CMD_SET_COLOR                      0x10                                                     //set color
#define    CMD_SET_EN_FONT                    0x1E                                                     //set english font
#define    CMD_SET_CH_FONT                    0x1F                                                     //set chinese font

#define    CMD_DRAW_PIXEL                     0x20                                                     //set pixel
#define    CMD_DRAW_LINE                      0x22                                                     //draw line
#define    CMD_FILL_RECT                      0x24                                                     //fill rectangle
#define    CMD_DRAW_CIRCLE                    0x26                                                     //draw circle
#define    CMD_FILL_CIRCLE                    0x27                                                     //fill circle
#define    CMD_DRAW_TRIANGLE                  0x28                                                     //draw triangle
#define    CMD_FILL_TRIANGLE                  0x29                                                     //fill triangle
#define    CMD_CLEAR                          0x2E                                                     //clear screen use back color

#define    CMD_DRAW_STRING                    0x30                                                     //draw string

#define    CMD_DRAW_BITMAP                    0x70                                                     //draw bitmap

/*
FONT
*/
#define    GBK32                              0x01
#define    GBK48                              0x02
#define    GBK64                              0x03
	
#define    ASCII32                            0x01
#define    ASCII48                            0x02
#define    ASCII64                            0x03

/*
Memory Mode
*/
#define    MEM_NAND                           0
#define    MEM_TF                             1

/*
set screen rotation
*/
#define    EPD_NORMAL                         0                                                        //screen normal
#define    EPD_INVERSION                      1      




class Jink_ {
    public:
        Jink_();
        ~Jink_();
		
        void begin();
        void begin(unsigned long);
        void begin(unsigned long, uint8_t, uint8_t);
        void begin(unsigned long, uint8_t, uint8_t, uint8_t);
        void begin(unsigned long, uint8_t, uint8_t, uint8_t, uint8_t);
		
        void end();
		
		void reset(void);
		void wakeup(void);
		
		void defaultConfig(void);

		void readBaud(void);
		void setBaud(long baud);
		void handshake(void);
		void setMemory(unsigned char mode);
		void enterStopmode(void);
		void udpate(void);
		void screenRotation(unsigned char mode);
		void loadFont(void);
		void loadPic(void);

		void setColor(unsigned char color, unsigned char bkcolor);
		void setEnglishFont(unsigned char font);
		void setChineseFont(unsigned char font);

		void drawPixel(int x0, int y0);
		void drawLine(int x0, int y0, int x1, int y1);
		void fillRect(int x0, int y0, int x1, int y1);
		void drawCircle(int x0, int y0, int r);
		void fillCircle(int x0, int y0, int r);
		void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
		void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
		void clear(void);

		void dispChar(unsigned char ch, int x0, int y0);
		void dispString(const void * p, int x0, int y0);
		void dispString(String str, int x0, int y0);
		
		void clearText();
		void persistText(String str);
		void persistTextLn(String str);
		void flushText(int x0, int y0, uint8_t size);

		void dispBitmap(const void * p, int x0, int y0);
		
    private:
	
		const unsigned long defaultBaudr = 115200;
		const uint8_t defaultRX = 8;
		const uint8_t defaultTX = 9;
		
		uint8_t _wakeup_pin = 10;
		uint8_t _reset_pin = 11;
		const char* LF_SEPARATOR = "§";

		const unsigned char _cmd_handshake[8] = {0xA5, 0x00, 0x09, CMD_HANDSHAKE, 0xCC, 0x33, 0xC3, 0x3C};				//CMD_HANDSHAKE
		const unsigned char _cmd_read_baud[8] = {0xA5, 0x00, 0x09, CMD_READ_BAUD, 0xCC, 0x33, 0xC3, 0x3C};				//CMD_READ_BAUD
		const unsigned char _cmd_stopmode[8] = {0xA5, 0x00, 0x09, CMD_STOPMODE, 0xCC, 0x33, 0xC3, 0x3C}; 				//CMD_STOPMODE
		const unsigned char _cmd_update[8] = {0xA5, 0x00, 0x09, CMD_UPDATE, 0xCC, 0x33, 0xC3, 0x3C}; 					//CMD_UPDATE
		const unsigned char _cmd_load_font[8] = {0xA5, 0x00, 0x09, CMD_LOAD_FONT, 0xCC, 0x33, 0xC3, 0x3C};				//CMD_LOAD_FONT
		const unsigned char _cmd_load_pic[8] = {0xA5, 0x00, 0x09, CMD_LOAD_PIC, 0xCC, 0x33, 0xC3, 0x3C}; 				//CMD_LOAD_PIC
		
		unsigned char _cmd_buff[CMD_SIZE];
		
		void _putchars(unsigned char * ptr, int n);
		unsigned char _verify(void * ptr, int n);

};

extern Jink_ Jink;

#endif