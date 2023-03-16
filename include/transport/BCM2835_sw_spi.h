//
// BCM2835_sw_spi (Raspberry Pi Nano, Software SPI) SPI interface for umcdi
//
// BCM2835 SDK Documentation:
//	* GPIO: https://www.airspayce.com/mikem/bcm2835/group__gpio.html
//
// Author: Tom Cully <mail@tomcully.com>
//
// Note: Software SPI is dramatically (x100+) less performant than Hardware SPI. Please consider using hardware SPI.

#ifndef UMCDI_TRANSPORT_BCM2835_SW
#define UMCDI_TRANSPORT_BCM2835_SW

#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdexcept>

#include "transport.h"

class BCM2835_sw_spi : Transport {
	void init(uint16_t sclkdelay, uint8_t gpio_dc, uint8_t gpio_rst, uint8_t gpio_cs, uint8_t gpio_sclk, uint8_t gpio_sdata);
	void shutdown();
	
	uint8_t read8();
	uint16_t read16();
	uint32_t read32();

	void write8(uint8_t data);
	void write16(uint16_t data);
	void write32(uint32_t data);

	uint32_t readBuffer(uint8_t* buffer, uint32_t length);
	uint32_t writeBuffer(uint8_t* buffer, uint32_t length);

	void writeCommand8(uint8_t cmd);
	void writeCommand16(uint16_t cmd);
	void writeCommand32(uint32_t cmd);
	uint32_t writeCommandBuffer(uint8_t* buffer, uint32_t length);

	void writeData8(uint8_t data);
	void writeData16(uint16_t data);
	void writeData32(uint32_t data);
	uint32_t writeDataBuffer(uint8_t* buffer, uint32_t length);

	void setDC(bool data);
	void setRST(bool data);

protected:
	uint8_t _cs;
	uint8_t _sclk;
	uint8_t _sdata;
	uint16_t _sclkdelay;

	void setCS(bool data);
	void setSCLK(bool data);
	void setSDATA(bool data);

	void delay(uint32_t ms);
};

#endif // UMCDI_TRANSPORT_BCM2835_SW