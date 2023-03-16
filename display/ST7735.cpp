#include "display/ST7735.h"

using namespace std;

void ST7735 ::init() {
	Rcmd1();
	Rcmd2red();
	Rcmd3();
	_transport->writeCommand8(ST7735_MADCTL);
	_transport->writeData8(0xC0);
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

void ST7735 ::Rcmd1() {
	_transport->writeCommand8(ST7735_SWRESET);
	_transport->sleep_ms(150);
	_transport->writeCommand8(ST7735_SLPOUT);
	_transport->sleep_ms(500);
	_transport->writeCommand8(ST7735_FRMCTR1);
	static uint8_t seq1[] { 0x01, 0x2C, 0x2D };
	_transport->writeDataBuffer(seq1, sizeof(seq1));
	_transport->writeCommand8(ST7735_FRMCTR2);
	_transport->writeDataBuffer(seq1, sizeof(seq1));
	_transport->writeCommand8(ST7735_FRMCTR3);
	static uint8_t seq2[] { 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D }; 
	_transport->writeDataBuffer(seq2, sizeof(seq2));
	_transport->writeCommand8(ST7735_INVCTR);
	_transport->writeData8(0x07);
	_transport->writeCommand8(ST7735_PWCTR1);
	static uint8_t seq3[] { 0xA2, 0x02, 0x84 }; 
	_transport->writeDataBuffer(seq3, sizeof(seq3));
	_transport->writeCommand8(ST7735_PWCTR2);
	_transport->writeData8(0xC5);
	_transport->writeCommand8(ST7735_PWCTR3);
	_transport->writeData8(0x0A);
	_transport->writeData8(0x00);
	_transport->writeCommand8(ST7735_PWCTR4);
	_transport->writeData8(0x8A);
	_transport->writeData8(0x2A);
	_transport->writeCommand8(ST7735_PWCTR5);
	_transport->writeData8(0x8A);
	_transport->writeData8(0xEE);
	_transport->writeCommand8(ST7735_VMCTR1);
	_transport->writeData8(0x0E);
	_transport->writeCommand8(ST7735_INVOFF);
	_transport->writeCommand8(ST7735_MADCTL);
	_transport->writeData8(0xC8);
	_transport->writeCommand8(ST7735_COLMOD);
	_transport->writeData8(0x05);
}

void ST7735 ::Rcmd2red() {
	_transport->writeCommand8(ST7735_CASET);
	static uint8_t seq1[] { 0x00, 0x00, 0x00, 0x7F };
	_transport->writeDataBuffer(seq1, sizeof(seq1));
	_transport->writeCommand8(ST7735_RASET);
	static uint8_t seq2[] { 0x00, 0x00, 0x00, 0x9F };
	_transport->writeDataBuffer(seq2, sizeof(seq2));
}

// Desc: init sub-routine

void ST7735 ::Rcmd3() {
	_transport->writeCommand8(ST7735_GMCTRP1);
	static uint8_t seq1[] { 0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10 };
	_transport->writeDataBuffer(seq1, sizeof(seq1));
	_transport->writeCommand8(ST7735_GMCTRN1);
	static uint8_t seq2[] { 0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10 };
	_transport->writeDataBuffer(seq2, sizeof(seq2));
	_transport->writeCommand8(ST7735_NORON);
	_transport->sleep_ms(10);
	_transport->writeCommand8(ST7735_DISPON);
	_transport->sleep_ms(100);
}