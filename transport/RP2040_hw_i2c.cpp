//
// RP2040_hw_i2c (Raspberry Pi Pico) I2C interface for umcdi
//
// RP2040 SDK Documentation:
//	* GPIO: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html
//  * I2C: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__i2c.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#include "transport/RP2040_hw_i2c.h"

#include "hardware/i2c.h"
#include "hardware/gpio.h"

using namespace std;

void RP2040_hw_i2c ::init(uint8_t i2cN, uint baudrate, uint8_t addr,  uint8_t gpio_dc, uint8_t gpio_rst) {
	// Save which GPIO pins have these functions
	_dc = gpio_dc;
	_rst = gpio_rst;

	// I2C Address
	_addr = addr;

	// Init GPIO
    gpio_init(_dc);
    gpio_init(_rst);
    gpio_set_dir(_dc, GPIO_OUT);
    gpio_set_dir(_rst, GPIO_OUT);

    // Init SPI
	switch (i2cN) {
		default:
		case 0:
			_i2c = i2c0;
			break;
		case 1:
			_i2c = i2c1;
			break;
			// throw std:runtime_error("Invalid SPI interface specifier for RP2040")
	}
	i2c_init(_i2c, baudrate);
}

void RP2040_hw_i2c ::shutdown() {
	i2c_deinit(_i2c);
	gpio_deinit(_dc);
	gpio_deinit(_rst);
}

uint8_t RP2040_hw_i2c ::read8() {
	uint8_t data;
	i2c_read_blocking(_i2c, _addr, &data, 1, false);
	return data;
}
uint16_t RP2040_hw_i2c ::read16() {
	uint16_t data;
	i2c_read_blocking(_i2c, _addr, (uint8_t*)(&data), 2, false);
	return data;
}
uint32_t RP2040_hw_i2c ::read32() {
	uint32_t data;
	i2c_read_blocking(_i2c, _addr, (uint8_t*)(&data), 4, false);
	return data;
}

void RP2040_hw_i2c ::write8(uint8_t data) {
	i2c_write_blocking(_i2c, _addr, (uint8_t*)(&data), 1, false);
}
void RP2040_hw_i2c ::write16(uint16_t data) {
	i2c_write_blocking(_i2c, _addr, (uint8_t*)(&data), 2, false);
}
void RP2040_hw_i2c ::write32(uint32_t data) {
	i2c_write_blocking(_i2c, _addr, (uint8_t*)(&data), 4, false);
}

void RP2040_hw_i2c ::sleep_ms(uint32_t ms) {
	sleep_ms(ms);
}

uint32_t RP2040_hw_i2c ::readBuffer(uint8_t* buffer, uint32_t length) {
	return i2c_read_blocking(_i2c, _addr, buffer, length, false);
}

uint32_t RP2040_hw_i2c ::writeBuffer(uint8_t* buffer, uint32_t length) {
	return i2c_write_blocking(_i2c, _addr, buffer, length, false);
}

void RP2040_hw_i2c ::setDC(bool data)
{
	gpio_put(_dc, data);
}
void RP2040_hw_i2c ::setRST(bool data)
{
	gpio_put(_rst, data);
}