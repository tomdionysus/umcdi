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

void BCM2835_sw_spi ::init(uint16_t clkdelay, uint8_t gpio_dc, gpio_rst, gpio_cs, gpio_sclk, gpio_sdata) {
	// Save which GPIO pins have these functions
	_dc = gpio_dc;
	_rst = gpio_rst;
	_cs = gpio_cs;
	_sclk = gpio_sclk;
	_sdata = gpio_sdata;
	_clkdelay = clkdelay;

	// Init GPIO
    gpio_init(_dc);
    gpio_init(_rst);
    gpio_init(_cs);
    gpio_init(_sclk);
    gpio_init(_sdata);
    gpio_init(_clkdelay);
    gpio_set_dir(_dc, GPIO_OUT);
    gpio_set_dir(_rst, GPIO_OUT);
    gpio_set_dir(_cs, GPIO_OUT);
    gpio_set_dir(_sclk, GPIO_OUT);
    gpio_set_dir(_sdata, GPIO_OUT);
    gpio_set_dir(_clkdelay, GPIO_OUT);
}

void RP2040_hw_spi ::shutdown() {
    gpio_deinit(_dc);
    gpio_deinit(_rst);
    gpio_deinit(_cs);
    gpio_deinit(_sclk);
    gpio_deinit(_sdata);
    gpio_deinit(_clkdelay);
}

uint8_t BCM2835_sw_spi ::read8() {
	throw std::runtime_error("Not Implemented");
}
uint16_t BCM2835_sw_spi ::read16() {
	throw std::runtime_error("Not Implemented");
}
uint32_t BCM2835_sw_spi ::read32() {
	throw std::runtime_error("Not Implemented");
}

void BCM2835_sw_spi ::write8(uint8_t data) {
	for (uint8_t i = 0; i < 8; i++) {
		setSDATA(false);
		if (spidata & 0x80) setSDATA(true); // b1000000 Mask with 0 & all zeros out.
		setSCLK(true);
		delay(_sclkdelay);
		spidata <<= 1;
		setSCLK(false);
		delay(_clkdelay);
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

void BCM2835_sw_spi ::writeCommand8(uint8_t cmd) {
	setDC(false);
	setCS(false)
	write8(cmd);
	setCS(true);
}
void BCM2835_sw_spi ::writeCommand16(uint16_t cmd) {
	setDC(false);
	setCS(false)
	write16(cmd);
	setCS(true);
}
void BCM2835_sw_spi ::writeCommand32(uint32_t cmd) {
	setDC(false);
	setCS(false)
	write32(cmd);
	setCS(true);
}

uint32_t BCM2835_sw_spi ::writeCommandBuffer(uint8_t* buffer, uint32_t length) {
	setDC(false);
	setCS(false)
	writeBuffer(buffer, length);
	setCS(true);
}

void BCM2835_sw_spi ::writeData8(uint8_t data) {
	setDC(true);
	setCS(false)
	write8(cmd);
	setCS(true);
}
void BCM2835_sw_spi ::writeData16(uint16_t data) {
	setDC(true);
	setCS(false)
	write16(cmd);
	setCS(true);
}
void BCM2835_sw_spi ::writeData32(uint32_t data) {
	setDC(true);
	setCS(false)
	write32(cmd);
	setCS(true);
}
uint32_t BCM2835_sw_spi ::writeDataBuffer(uint8_t* buffer, uint32_t length) {
	setDC(true);
	setCS(false)
	writeBuffer(buffer, length);
	setCS(true);
}

uint32_t BCM2835_sw_spi ::readBuffer(uint8_t* buffer, uint32_t length) {
	throw std::runtime_error("Not Implemented");
}

uint32_t BCM2835_sw_spi ::writeBuffer(uint8_t* buffer, uint32_t length) {
	for(uint32_t i=0; i<length; i++) {
		write(spidata[i]);
	}
	return length;
}

void BCM2835_sw_spi ::setDC(bool data)
{
	bcm2835_gpio_write(_cs, data ? HIGH : LOW)
}
void BCM2835_sw_spi ::setCS(bool data)
{
	bcm2835_gpio_write(_rst, data ? HIGH : LOW)
}
void BCM2835_sw_spi ::setRST(bool data)
{
	bcm2835_gpio_write(_dc, data ? HIGH : LOW)
}
void BCM2835_sw_spi ::setSCLK(bool data)
{
	bcm2835_gpio_write(_sclk, data ? HIGH : LOW)
}
void BCM2835_sw_spi ::setSDATA(bool data)
{
	bcm2835_gpio_write(_sdata, data ? HIGH : LOW)
}
