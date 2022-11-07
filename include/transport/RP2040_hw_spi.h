//
// RP2040_hw_spi (Raspberry Pi Pico) SPI interface for umcdi
//
// RP2040 SDK Documentation:
//	* GPIO: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html
//  * SPI: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__spi.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdexcept>

#include "pico/stdlib.h"

#include "transport.h"

class RP2040_hw_spi : Transport {
	void init(uint8_t spiX, uint baudrate, uint8_t gpio_dc, gpio_rst);
	void init(uint8_t spiX, uint baudrate, uint8_t gpio_dc, gpio_rst, uint data_bits, spi_cpol_t cpol, spi_cpha_t cpha, spi_order_t order);
	void shutdown();
};