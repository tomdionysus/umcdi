//
// BCM2835_hw_spi (Raspberry Pi Nano, Hardware SPI) SPI interface for umcdi
//
// BCM2835 SDK Documentation:
//	* GPIO: https://www.airspayce.com/mikem/bcm2835/group__gpio.html
//	* SPI: https://www.airspayce.com/mikem/bcm2835/group__spi.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

class BCM2835_hw_spi : public Transport {
	void init(uint8_t spiX, uint frequency, uint8_t gpio_dc, gpio_rst);
	void init(uint8_t spiX, uint frequency, uint8_t gpio_dc, gpio_rst, uint8_t bitorder, datamde);
}