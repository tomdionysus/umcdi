//
// RP2040_hw_spi (Raspberry Pi Pico) SPI interface for umcdi
//
// RP2040 SDK Documentation:
//	* GPIO: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html
//  * SPI: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__spi.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#include "transport/RP2040_hw_spi.h"

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
			throw std:runtime_error("Invalid SPI interface specifier for RP2040")
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

uint8_t RP2040_hw_spi ::read8() {
	uint8_t data;
	spi_read_blocking(_spi, &data, 1);
	return data;
}
uint16_t RP2040_hw_spi ::read16() {
	uint16_t data;
	spi_read_blocking(_spi, &data, 2);
	return data;
}
uint32_t RP2040_hw_spi ::read32() {
	uint32_t data;
	spi_read_blocking(_spi, &data, 4);
	return data;
}

void RP2040_hw_spi ::write8(uint8_t data) {
	spi_write_blocking(_spi, &data, 1);
}
void RP2040_hw_spi ::write16(uint16_t data) {
	spi_write_blocking(_spi, &data, 2);
}
void RP2040_hw_spi ::write32(uint32_t data) {
	spi_write_blocking(_spi, &data, 4);
}

uint32_t RP2040_hw_spi ::readBuffer(uint8_t* buffer, uint32_t length) {
	return spi_read_blocking(_spi, &buffer, length);
}

uint32_t RP2040_hw_spi ::writeBuffer(uint8_t* buffer, uint32_t length) {
	return spi_write_blocking(_spi, &buffer, length);
}

void RP2040_hw_spi ::setDC(bool data)
{
	gpio_put(_dc, data)
}
void RP2040_hw_spi ::setRST(bool data)
{
	gpio_put(_rst, data)
}