#include <stdexcept>

#include "transport.h"

#ifndef UMCDI_DISPLAY
#define UMCDI_DISPLAY

class Display {

public:
	virtual void drawPixel(uint16_t x, uint16_t y, uint32_t color) = 0;
	virtual void drawBitmap16(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h) = 0;
	virtual void drawBitmap24(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h) = 0;

	virtual void fillRectangle(uint16_t x, uint16_t y, uint16_t w, int16_t h, uint32_t color);
	virtual void fillScreen(uint32_t color);

	virtual void setRotation(uint8_t rot);

protected:
	Transport *_transport;
	uint16_t _width;
	uint16_t _height;

	uint16_t rgb24torgb565(uint32_t rgb24);
	uint32_t rgb565torgb24(uint16_t rgb565);
};

#endif // UMCDI_DISPLAY