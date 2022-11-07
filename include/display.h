#include <stdint.h>
#include <stdexcept>

#include "transport.h"

class Display {

public:

	Display(Transport *transport, uint16_t width, uint16_t height);
	~Display();

	virtual void drawPixel(uint16_t x, uint16_t y, uint32_t color);
	virtual void drawBitmap16(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h);
	virtual void drawBitmap24(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h);
	virtual void fillRectangle(uint16_t x, uint16_t y, uint16_t w, int16_t h, uint32_t color);
	virtual void fillScreen(uint32_t color);

protected:

	Transport *_transport;
	uint16_t _width;
	uint16_t _height;

	uint16_t rgb24torgb565(uint32_t rgb24);
	uint32_t rgb565torgb24(uint16_t rgb565);
};