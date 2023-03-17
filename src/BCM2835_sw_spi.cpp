//
// BCM2835_sw_spi (Raspberry Pi Nano) SPI interface for umcdi
//
// BCM2835 SDK Documentation:
//	* GPIO: https://www.airspayce.com/mikem/bcm2835/group__gpio.html
//
// Author: Tom Cully <mail@tomcully.com>
//
// Note: Software SPI is dramatically (x100+) less performant than Hardware SPI. Please consider using hardware SPI.

#include "BCM2835_sw_spi.h"
using namespace std;

void BCM2835_sw_spi ::init(uint16_t sclkdelay_ms, uint8_t gpio_dc, uint8_t gpio_rst, uint8_t gpio_cs, uint8_t gpio_sclk, uint8_t gpio_sdata) {
	// Save which GPIO pins have these functions
	_dc = gpio_dc;
	_rst = gpio_rst;
	_cs = gpio_cs;
	_sclk = gpio_sclk;
	_sdata = gpio_sdata;
	_sclkdelay_ms = sclkdelay_ms;

	// Init GPIO
    bcm2835_gpio_fsel(_dc, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(_rst, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(_cs, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(_sclk, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(_sdata, BCM2835_GPIO_FSEL_OUTP);
}

void BCM2835_sw_spi ::shutdown() {
}

uint8_t BCM2835_sw_spi ::read8() {
	// throw std::runtime_error("Not Implemented");
	return 0;
}
uint16_t BCM2835_sw_spi ::read16() {
	// throw std::runtime_error("Not Implemented");
	return 0;
}
uint32_t BCM2835_sw_spi ::read32() {
	// throw std::runtime_error("Not Implemented");
	return 0;
}

void BCM2835_sw_spi ::write8(uint8_t data) {
	for (uint8_t i = 0; i < 8; i++) {
		setSDATA(false);
		if (data & 0x80) setSDATA(true); // b1000000 Mask with 0 & all zeros out.
		setSCLK(true);
		delay_ms(_sclkdelay_ms);
		data <<= 1;
		setSCLK(false);
		BCM2835_sw_spi::delay_ms(_sclkdelay_ms);
	}
}
void BCM2835_sw_spi ::write16(uint16_t data) {
	write8(data >> 8);
	write8(data);
}
void BCM2835_sw_spi ::write32(uint32_t data) {
	write8(data >> 24);
	write8(data >> 16);
	write8(data >> 8);
	write8(data);
}

void BCM2835_sw_spi ::delay_ms(uint32_t ms) {
	bcm2835_delay(ms);
}

void BCM2835_sw_spi ::writeCommand8(uint8_t cmd) {
	setDC(false);
	setCS(false);
	write8(cmd);
	setCS(true);
}
void BCM2835_sw_spi ::writeCommand16(uint16_t cmd) {
	setDC(false);
	setCS(false);
	write16(cmd);
	setCS(true);
}
void BCM2835_sw_spi ::writeCommand32(uint32_t cmd) {
	setDC(false);
	setCS(false);
	write32(cmd);
	setCS(true);
}

uint32_t BCM2835_sw_spi ::writeCommandBuffer(uint8_t* buffer, uint32_t length) {
	setDC(false);
	setCS(false);
	uint32_t wlen = writeBuffer(buffer, length);
	setCS(true);
	return wlen;
}

void BCM2835_sw_spi ::writeData8(uint8_t data) {
	setDC(true);
	setCS(false);
	write8(data);
	setCS(true);
}
void BCM2835_sw_spi ::writeData16(uint16_t data) {
	setDC(true);
	setCS(false);
	write16(data);
	setCS(true);
}
void BCM2835_sw_spi ::writeData32(uint32_t data) {
	setDC(true);
	setCS(false);
	write32(data);
	setCS(true);
}
uint32_t BCM2835_sw_spi ::writeDataBuffer(uint8_t* buffer, uint32_t length) {
	setDC(true);
	setCS(false);
	uint32_t rlen = writeBuffer(buffer, length);
	setCS(true);
	return rlen;
}

uint32_t BCM2835_sw_spi ::readBuffer(uint8_t* buffer, uint32_t length) {
	// throw std::runtime_error("Not Implemented");
	return 0;
}

uint32_t BCM2835_sw_spi ::writeBuffer(uint8_t* buffer, uint32_t length) {
	for(uint32_t i=0; i<length; i++) {
		write8(buffer[i]);
	}
	return length;
}

void BCM2835_sw_spi ::setDC(bool data) {
	bcm2835_gpio_write(_dc, data ? HIGH : LOW);
}

void BCM2835_sw_spi ::setCS(bool data) {
	bcm2835_gpio_write(_cs, data ? HIGH : LOW);
}

void BCM2835_sw_spi ::setRST(bool data) {
	bcm2835_gpio_write(_rst, data ? HIGH : LOW);
}

void BCM2835_sw_spi ::setSCLK(bool data) {
	bcm2835_gpio_write(_sclk, data ? HIGH : LOW);
}

void BCM2835_sw_spi ::setSDATA(bool data) {
	bcm2835_gpio_write(_sdata, data ? HIGH : LOW);
}