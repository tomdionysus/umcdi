#include "ST7735.h"

using namespace std;

ST7735 ::ST7735(Transport *transport, uint16_t width, uint16_t height) {
	_transport = transport;
	_width = width;
	_height = height;
}

void ST7735 ::init() {

	_transport->setRST(false);
	_transport->delay_ms(200);

	_transport->setRST(true);
	_transport->delay_ms(20);
	
	_transport->writeCommand8(0x11);	// turn off sleep mode
	_transport->delay_ms(100);

	_transport->writeCommand8(0x21);	// display inversion mode

	_transport->writeCommand8(0xB1);	// Set the frame frequency of the full colors normal mode
									// Frame rate=fosc/((RTNA x 2 + 40) x (LINE + FPA + BPA +2))
									// fosc = 850kHz
	_transport->writeData8(0x05);	// RTNA
	_transport->writeData8(0x3A);	// FPA
	_transport->writeData8(0x3A);	// BPA

	_transport->writeCommand8(0xB2);	// Set the frame frequency of the Idle mode
									// Frame rate=fosc/((RTNB x 2 + 40) x (LINE + FPB + BPB +2))
									// fosc = 850kHz
	_transport->writeData8(0x05);	// RTNB
	_transport->writeData8(0x3A);	// FPB
	_transport->writeData8(0x3A);	// BPB

	_transport->writeCommand8(0xB3);	// Set the frame frequency of the Partial mode/ full colors
	_transport->writeData8(0x05);  
	_transport->writeData8(0x3A);
	_transport->writeData8(0x3A);
	_transport->writeData8(0x05);
	_transport->writeData8(0x3A);
	_transport->writeData8(0x3A);

	_transport->writeCommand8(0xB4);
	_transport->writeData8(0x03);

	_transport->writeCommand8(0xC0);
	_transport->writeData8(0x62);
	_transport->writeData8(0x02);
	_transport->writeData8(0x04);

	_transport->writeCommand8(0xC1);
	_transport->writeData8(0xC0);

	_transport->writeCommand8(0xC2);
	_transport->writeData8(0x0D);
	_transport->writeData8(0x00);

	_transport->writeCommand8(0xC3);
	_transport->writeData8(0x8D);
	_transport->writeData8(0x6A);   

	_transport->writeCommand8(0xC4);
	_transport->writeData8(0x8D); 
	_transport->writeData8(0xEE); 

	_transport->writeCommand8(0xC5);  /*VCOM*/
	_transport->writeData8(0x0E);    

	_transport->writeCommand8(0xE0);
	_transport->writeData8(0x10);
	_transport->writeData8(0x0E);
	_transport->writeData8(0x02);
	_transport->writeData8(0x03);
	_transport->writeData8(0x0E);
	_transport->writeData8(0x07);
	_transport->writeData8(0x02);
	_transport->writeData8(0x07);
	_transport->writeData8(0x0A);
	_transport->writeData8(0x12);
	_transport->writeData8(0x27);
	_transport->writeData8(0x37);
	_transport->writeData8(0x00);
	_transport->writeData8(0x0D);
	_transport->writeData8(0x0E);
	_transport->writeData8(0x10);

	_transport->writeCommand8(0xE1);
	_transport->writeData8(0x10);
	_transport->writeData8(0x0E);
	_transport->writeData8(0x03);
	_transport->writeData8(0x03);
	_transport->writeData8(0x0F);
	_transport->writeData8(0x06);
	_transport->writeData8(0x02);
	_transport->writeData8(0x08);
	_transport->writeData8(0x0A);
	_transport->writeData8(0x13);
	_transport->writeData8(0x26);
	_transport->writeData8(0x36);
	_transport->writeData8(0x00);
	_transport->writeData8(0x0D);
	_transport->writeData8(0x0E);
	_transport->writeData8(0x10);

	_transport->writeCommand8(0x3A);	// define the format of RGB picture data
	_transport->writeData8(0x05);	// 16-bit/pixel

	setRotation(0);

	_transport->writeCommand8(0x29);	// Display On
}

void ST7735 ::drawPixel(uint16_t x, uint16_t y, uint32_t color) {
	if ((x >= _width) || (y >= _height)) return;
	setWindow(x, y, x + 1, y + 1);
	_transport->writeData16(rgb24torgb565(color));
}

void ST7735 ::setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	_transport->writeCommand8(ST7735_CASET);
	_transport->writeData16(x0 + _XStart);
	_transport->writeData16(x1 + _XStart);
	_transport->writeCommand8(ST7735_RASET);
	_transport->writeData16(y0 +_YStart);
	_transport->writeData16(y1 +_YStart);
	_transport->writeCommand8(ST7735_RAMWR);
}

void ST7735 ::drawBitmap16(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h) {
	uint8_t i, j;
	uint16_t color;
	uint32_t ptr;
	
	// Check bounds
	if ((x >= _width) || (y >= _height)) return;
	if ((x + w - 1) >= _width) w = _width - x;
	if ((y + h - 1) >= _height) h = _height - y;
	
	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w * h * 2);
	ptr = 0;
	
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w; i ++)
		{
			color = *(unsigned int*)(pBmp + i * 2 + (h-1-j) * 2 * w);
			buffer[ptr++] = color >> 8;
			buffer[ptr++] = color;
		}
	}
	
	// Set window and write buffer
	setWindow(x, y, x + w - 1, y + h - 1);
	_transport->writeDataBuffer(buffer, w * h * 2);

	free(buffer);
}

void ST7735 ::drawBitmap24(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h) {
	uint8_t i, j;
	uint16_t color;
	uint32_t rgb, ptr;

	// Check bounds
	if ((x >= _width) || (y >= _height)) return;
	if ((x + w - 1) >= _width) w = _width - x;
	if ((y + h - 1) >= _height) h = _height - y;
	
	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w * h * 2);

	ptr = 0;
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w ; i ++)
		{
			// Translate RBG24 to RGB565 bitmap 
			rgb = *(unsigned int*)(pBmp + i * 3 + (h-1-j) * 3 * w);
			color = rgb24torgb565(rgb);
			buffer[ptr++] = color >> 8;
			buffer[ptr++] = color;
		}
	}

	// Set window and write buffer
	setWindow(x, y, x + w - 1, y + h - 1);
	_transport->writeDataBuffer(buffer, w * h * 2);

	free(buffer);
}

void ST7735 ::fillRectangle(uint16_t x, uint16_t y, uint16_t w, int16_t h, uint32_t rgb24) {
	uint8_t hi, lo;

	uint16_t color = rgb24torgb565(rgb24);

	// Check bounds
	if ((x >= _width) || (y >= _height)) return;
	if ((x + w - 1) >= _width) w = _width - x;
	if ((y + h - 1) >= _height) h = _height - y;
	
	// Colour to bytes
	hi = color >> 8;
	lo = color;

	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w * h * 2);
	for(uint32_t i = 0; i<(w * h * 2);) {
		buffer[i++] = hi;
		buffer[i++] = lo;
	}

	// Set window and write buffer
	setWindow(x, y, x + w - 1, y + h - 1);
	_transport->writeDataBuffer(buffer, h * w * 2);

	free(buffer);
}

void ST7735 ::fillScreen(uint32_t rgb24) {
	fillRectangle(0, 0, _width, _height, rgb24);
}

uint16_t ST7735 ::rgb24torgb565(uint32_t rgb24) {
	return (((rgb24 >> 16) & 0xF8) << 8) | (((rgb24 >> 8) & 0xFC) << 3) | ((rgb24 & 0xFF) >> 3);
}

void ST7735 ::setRotation(uint8_t rot)
{
	// Memory data access control (MADCTL)
	_transport->writeCommand8(0x36);
	if(rot == 0) _transport->writeData8(0x00 | (1<<3));
	else if(rot == 1) _transport->writeData8(0xC0 | (1<<3));
	else if(rot == 2) _transport->writeData8(0x70 | (1<<3));
	else _transport->writeData8(0xA0 | (1<<3));
}