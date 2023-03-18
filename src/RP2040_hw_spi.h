//
// RP2040_hw_spi (Raspberry Pi Pico) SPI interface for umcdi
//
// RP2040 SDK Documentation:
//	* GPIO: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html
//  * SPI: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__spi.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#ifndef UMCDI_TRANSPORT_RP2040_HW
#define UMCDI_TRANSPORT_RP2040_HW

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "transport.h"

#include "hardware/spi.h"

class RP2040_hw_spi : public Transport {
public:
	void init(uint8_t spiX, uint baudrate, uint8_t gpio_dc, uint8_t gpio_rst, uint8_t gpio_cs, uint8_t gpio_scl, uint8_t gpio_sda);
	void shutdown();

	// Read 8/16/32 bits
	uint8_t read8();
	uint16_t read16();
	uint32_t read32();

	// Write 8/16/32 bits
	void write8(uint8_t data) override;
	void write16(uint16_t data) override;
	void write32(uint32_t data) override;

	void delay_ms(uint32_t ms) override;

	// Read into a buffer, up to length bytes. Return no. of read bytes
	uint32_t readBuffer(uint8_t* buffer, uint32_t length) override;
	// Write from a buffer, length bytes. Return no. of written bytes
	uint32_t writeBuffer(uint8_t* buffer, uint32_t length) override;

	// Set Data/Control
	void setDC(bool data) override;
	// Set Reset
	void setRST(bool data) override;
	// Set CS
	void setCS(bool data) override;

protected:
	spi_inst_t* _spi;

	uint8_t _scl;
	uint8_t _sda;
};

#endif // UMCDI_TRANSPORT_RP2040_HW