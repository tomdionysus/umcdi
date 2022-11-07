//
// BCM2835_sw_spi (Raspberry Pi Nano, Software SPI) SPI interface for umcdi
//
// BCM2835 SDK Documentation:
//	* GPIO: https://www.airspayce.com/mikem/bcm2835/group__gpio.html
//
// Author: Tom Cully <mail@tomcully.com>
//
// Note: Software SPI is dramatically (x100+) less performant than Hardware SPI. Please consider using hardware SPI.

#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

class BCM2835_sw_spi : public Transport {
	void init(uint16_t clkdelay, uint8_t gpio_dc, gpio_rst, gpio_cs, gpio_sclk, gpio_sdata);

protected:
	uint8_t _cs;
	uint8_t _sclk;
	uint8_t _sdata;
	uint16_t _clkdelay;

	// Set Chip Select
	void setCS(bool data);
	// Set SCLK (bit bang CLOCK)
	void setSCLK(bool data);
	// Set SDATA (bit bang DATA)
	void setSDATA(bool data);

	virtual delay(uint32_t ms);
}