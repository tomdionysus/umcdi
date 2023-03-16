//
// ST7735 Display driver for umcdi
//
// ST7735 SDK Documentation:
//	* https://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
//
// Author: Tom Cully <mail@tomcully.com>
//

#ifndef UMCDI_DISPLAY_ST7735
#define UMCDI_DISPLAY_ST7735

#include <stdint.h>
#include <stdlib.h>
#include "display.h"

#define ST7735_NOP     0x00 // Non operation
#define ST7735_SWRESET 0x01 // Soft Reset
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10 // Sleep ON
#define ST7735_SLPOUT  0x11 // Sleep OFF
#define ST7735_PTLON   0x12 // Partial mode
#define ST7735_NORON   0x13 // Normal Display
#define ST7735_INVOFF  0x20 // Display invert off
#define ST7735_INVON   0x21 // Display Invert on
#define ST7735_DISPOFF 0x28 // Display off
#define ST7735_DISPON  0x29 // Display on

#define ST7735_TFT_Idle_modeON 0x39 //Idle Mode ON
#define ST7735_TFT_Idle_modeOF  0x38 //Idle Mode OFF

#define ST7735_CASET   0x2A // Column address set
#define ST7735_RASET   0x2B // Page address set
#define ST7735_RAMWR   0x2C // Memory write
#define ST7735_RAMRD   0x2E // Memory read
#define ST7735_PTLAR   0x30 // Partial Area
#define ST7735_VSCRDEF 0x33 // Vertical scroll def
#define ST7735_COLMOD  0x3A // Interface Pixel Format
#define ST7735_MADCTL  0x36 // Memory Access Control
#define ST7735_VSCRSADD 0x37 // Vertical Access Control

// Frame Rate Control
#define ST7735_FRMCTR1 0xB1 // Normal
#define ST7735_FRMCTR2 0xB2 // idle
#define ST7735_FRMCTR3 0xB3 // Partial

#define ST7735_INVCTR  0xB4 // Display Inversion control
#define ST7735_DISSET5 0xB6 // Display Function set

// Power_Control
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_PWCTR6  0xFC

#define ST7735_VMCTR1  0xC5 // VCOM_Control 1

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_GMCTRP1 0xE0 // Positive Gamma Correction Setting
#define ST7735_GMCTRN1 0xE1 // Negative Gamma Correction Setting

#define ST7735_MADCTL_MY 0x80
#define ST7735_MADCTL_MX 0x40
#define ST7735_MADCTL_MV 0x20
#define ST7735_MADCTL_ML 0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH 0x04

// Color definitions 16-Bit Color Values R5G6B5
#define  ST7735_BLACK   0x0000
#define  ST7735_BLUE    0x001F
#define  ST7735_RED     0xF800
#define  ST7735_GREEN   0x07E0
#define  ST7735_CYAN    0x07FF
#define  ST7735_MAGENTA 0xF81F
#define  ST7735_YELLOW  0xFFE0
#define  ST7735_WHITE   0xFFFF
#define  ST7735_TAN     0xED01
#define  ST7735_GREY    0x9CD1
#define  ST7735_BROWN   0x6201

// Delays
#define TFT_MILLISEC_DELAY bcm2835_delay
#define TFT_MICROSEC_DELAY bcm2835_delayMicroseconds
#define TFT_HIGHFREQ_DELAY 0 // Optional Software SPI delay uS

class ST7735 : public Display {

public:
	ST7735(Transport *transport, uint16_t width, uint16_t height) : Display(transport, width, height) {};

	void init();

	void Rcmd1();
	void Rcmd2red();
	void Rcmd3();

	void drawPixel(uint16_t x, uint16_t y, uint32_t color);
	void drawBitmap16(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h);
	void drawBitmap24(uint16_t x, uint16_t y, uint8_t *pBmp, uint16_t w, uint16_t h);
	void fillRectangle(uint16_t x, uint16_t y, uint16_t w, int16_t h, uint32_t color);
	void fillScreen(uint32_t color);

protected:
	uint16_t _XStart;
	uint16_t _YStart;

	void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	uint16_t rgb24torgb565(uint32_t rgb24);
};

#endif // UMCDI_DISPLAY_ST7735
