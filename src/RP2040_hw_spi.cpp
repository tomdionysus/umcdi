//
// RP2040_hw_spi (Raspberry Pi Pico) SPI interface for umcdi
//
// RP2040 SDK Documentation:
//	* GPIO: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html
//  * SPI: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__spi.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#include "RP2040_hw_spi.h"

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

using namespace std;

void RP2040_hw_spi ::init(uint8_t spiX, uint baudrate, uint8_t gpio_dc, uint8_t gpio_rst, uint8_t gpio_cs, uint8_t gpio_scl, uint8_t gpio_sda) {
	// Save which GPIO pins have these functions
	_dc = gpio_dc;
	_rst = gpio_rst;
	_cs = gpio_cs;
	_scl = gpio_scl;
	_sda = gpio_sda;

	// Init GPIO
    gpio_init(_dc);
    gpio_set_dir(_dc, GPIO_OUT);

    gpio_init(_rst);
    gpio_set_dir(_rst, GPIO_OUT);

    // Init SPI
	if(spiX == 0) _spi = spi0; else _spi = spi1;

    gpio_init(_scl);
	gpio_set_function(_scl, GPIO_FUNC_SPI);

	gpio_init(_sda);
	gpio_set_function(_sda, GPIO_FUNC_SPI);

    gpio_init(_cs);
    gpio_set_dir(_cs, GPIO_OUT);

	spi_init(_spi, baudrate);
	
	/* SPI parameter config */
	spi_set_format(_spi,
		8, /* data_bits */
		SPI_CPOL_0, /* cpol */
		SPI_CPHA_0, /* cpha */
		SPI_MSB_FIRST /* order */
	);

	setCS(true);	// Active Low
	setRST(false);
}

void RP2040_hw_spi ::shutdown() {
	spi_deinit(_spi);
	gpio_deinit(_dc);
	gpio_deinit(_rst);
	gpio_deinit(_cs);
	gpio_deinit(_scl);
	gpio_deinit(_sda);
}

uint8_t RP2040_hw_spi ::read8() {
	uint8_t data;
	setCS(false);
	spi_read_blocking(_spi, 1, &data, 1);
	setCS(true);
	return data;
}
uint16_t RP2040_hw_spi ::read16() {
	uint16_t data;
	setCS(false);
	spi_read_blocking(_spi, 1, (uint8_t*)(&data), 2);
	setCS(true);
	return data;
}
uint32_t RP2040_hw_spi ::read32() {
	uint32_t data;
	setCS(false);
	spi_read_blocking(_spi, 1, (uint8_t*)(&data), 4);
	setCS(true);
	return data;
}

void RP2040_hw_spi ::write8(uint8_t data) {
	setCS(false);
	spi_write_blocking(_spi, (uint8_t*)(&data), 1);
	setCS(true);
}
void RP2040_hw_spi ::write16(uint16_t data) {
	setCS(false);
	spi_write_blocking(_spi, (uint8_t*)(&data), 2);
	setCS(true);
}
void RP2040_hw_spi ::write32(uint32_t data) {
	setCS(false);
	spi_write_blocking(_spi, (uint8_t*)(&data), 4);
	setCS(true);
}

void RP2040_hw_spi ::delay_ms(uint32_t ms) {
	sleep_ms(ms);
}

uint32_t RP2040_hw_spi ::readBuffer(uint8_t* buffer, uint32_t length) {
	setCS(false);
	uint32_t iolen = spi_read_blocking(_spi, 1, buffer, length);
	setCS(true);
	return iolen;
}

uint32_t RP2040_hw_spi ::writeBuffer(uint8_t* buffer, uint32_t length) {
	setCS(false);
	uint32_t iolen = spi_write_blocking(_spi, buffer, length);
	setCS(true);
	return iolen;
}

void RP2040_hw_spi ::setDC(bool data)
{
	gpio_put(_dc, data);
}

void RP2040_hw_spi ::setRST(bool data)
{
	gpio_put(_rst, data);
}

void RP2040_hw_spi ::setCS(bool data)
{
	gpio_put(_cs, data);
}