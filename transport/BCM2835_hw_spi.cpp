//
// BCM2835_hw_spi (Raspberry Pi Nano, Hardware SPI) SPI interface for umcdi
//
// BCM2835 SDK Documentation:
//	* GPIO: https://www.airspayce.com/mikem/bcm2835/group__gpio.html
//	* SPI: https://www.airspayce.com/mikem/bcm2835/group__spi.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#include "BCM2835_hw_spi.h"
using namespace std;

void RP2040_hw_spi ::init(uint8_t spiX, uint baudrate, uint8_t gpio_dc, gpio_rst) {
	// Save which GPIO pins have these functions
	_dc = gpio_dc;
	_rst = gpio_rst;

	// Init GPIO
    gpio_init(_dc);
    gpio_init(_rst);
    gpio_set_dir(_dc, GPIO_OUT);
    gpio_set_dir(_rst, GPIO_OUT);

    // Init SPI
	switch spiX {
		case 0:
			_spi = spi0;
			break;
		case 1:
			_spi = spi1;
			break;
		default:
			throw std:runtime_error("Invalid SPI interface specifier for BCM2835")
	}
	spi_init(_spi,baudrate);
	spi_set_slave(_spi, false);
}

void RP2040_hw_spi ::init(uint8_t spiX, uint baudrate, uint8_t gpio_dc, gpio_rst, uint data_bits, spi_cpol_t cpol, spi_cpha_t cpha, spi_order_t order) {
	init(spiX, baudrate, gpio_dc, gpio_rst);
	spi_set_format(_spi, data_bits, cpol, cpha, order);
}

void RP2040_hw_spi ::shutdown() {
	spi_deinit(_spi);
	gpio_deinit(_dc);
	gpio_deinit(_rst);
}

uint8_t BCM2835_hw_spi ::read8() {
	throw std::runtime_error("Not Implemented");
}
uint16_t BCM2835_hw_spi ::read16() {
	throw std::runtime_error("Not Implemented");
}
uint32_t BCM2835_hw_spi ::read32() {
	throw std::runtime_error("Not Implemented");
}

void BCM2835_hw_spi ::write8(uint8_t data) {
	bcm2835_spi_transfer(data);
}
void BCM2835_hw_spi ::write16(uint16_t data) {
	bcm2835_spi_transfer(data >> 8);
	bcm2835_spi_transfer(data);
}
void BCM2835_hw_spi ::write32(uint32_t data) {
	bcm2835_spi_transfer(data >> 24);
	bcm2835_spi_transfer(data >> 16);
	bcm2835_spi_transfer(data >> 8);
	bcm2835_spi_transfer(data);
}

uint32_t BCM2835_hw_spi ::readBuffer(uint8_t* buffer, uint32_t length) {
	throw std::runtime_error("Not Implemented");
}

uint32_t BCM2835_hw_spi ::writeBuffer(uint8_t* buffer, uint32_t length) {
	return bcm2835_spi_writenb((char*)spidata,len);
}

void BCM2835_hw_spi ::setDC(bool data)
{
	bcm2835_gpio_write(_cs, data ? HIGH : LOW)
}
void BCM2835_hw_spi ::setRST(bool data)
{
	bcm2835_gpio_write(_dc, data ? HIGH : LOW)
}
