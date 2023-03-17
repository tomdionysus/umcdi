#include "display.h"

void Display ::fillRectangle(uint16_t x, uint16_t y, uint16_t w, int16_t h, uint32_t rgb24) {
	uint8_t i, j;
	uint32_t rgb, ptr;

	// Check bounds
	if ((x >= _width) || (y >= _height)) return;
	if ((x + w - 1) >= _width) w = _width - x;
	if ((y + h - 1) >= _height) h = _height - y;
	
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w ; i ++)
		{
			drawPixel(i,j, rgb24);
		}
	}
}

void Display ::fillScreen(uint32_t rgb24) {
	uint8_t i, j;
	
	for(j = 0; j < _height; j++)
	{
		for(i = 0; i < _width; i ++)
		{
			drawPixel(i,j, rgb24);
		}
	}
}
