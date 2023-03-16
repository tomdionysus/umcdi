//
// BCM2835_hw_spi (Raspberry Pi Nano, Hardware SPI) SPI interface for umcdi
//
// BCM2835 SDK Documentation:
//	* GPIO: https://www.airspayce.com/mikem/bcm2835/group__gpio.html
//	* SPI: https://www.airspayce.com/mikem/bcm2835/group__spi.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#ifndef UMCDI_TRANSPORT_BCM2835_HW
#define UMCDI_TRANSPORT_BCM2835_HW

#include <bcm2835.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdexcept>

#include "transport.h"

class BCM2835_hw_spi : Transport {
	void init(uint16_t clockDivider, uint8_t gpio_dc, uint8_t gpio_rst);
	void shutdown();

	uint8_t read8();
	uint16_t read16();
	uint32_t read32();

	void write8(uint8_t data);
	void write16(uint16_t data);
	void write32(uint32_t data);

	void sleep_ms(uint32_t ms);

	uint32_t readBuffer(uint8_t* buffer, uint32_t length);
	uint32_t writeBuffer(uint8_t* buffer, uint32_t length);

	void setDC(bool data);
	void setRST(bool data);

protected:
	uint8_t _spi;
};

#endif // UMCDI_TRANSPORT_BCM2835_HW