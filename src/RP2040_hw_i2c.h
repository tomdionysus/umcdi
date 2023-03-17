//
// RP2040_hw_i2c (Raspberry Pi Pico) SPI interface for umcdi
//
// RP2040 SDK Documentation:
//	* GPIO: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html
//  * SPI: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__i2c.html
//
// Author: Tom Cully <mail@tomcully.com>
//

#ifndef UMCDI_TRANSPORT_RP2040_HW_I2C
#define UMCDI_TRANSPORT_RP2040_HW_I2C

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "transport.h"

#include "hardware/i2c.h"

class RP2040_hw_i2c : public Transport {
public:
	void init(uint8_t i2cN, uint baudrate, uint8_t addr, uint8_t gpio_dc, uint8_t gpio_rst);
	void shutdown();

	// Read 8/16/32 bits
	uint8_t read8();
	uint16_t read16();
	uint32_t read32();

	// Write 8/16/32 bits
	void write8(uint8_t data);
	void write16(uint16_t data);
	void write32(uint32_t data);

	void delay_ms(uint32_t ms);

	// Read into a buffer, up to length bytes. Return no. of read bytes
	uint32_t readBuffer(uint8_t* buffer, uint32_t length);
	// Write from a buffer, length bytes. Return no. of written bytes
	uint32_t writeBuffer(uint8_t* buffer, uint32_t length);

	// Set Data/Control
	void setDC(bool data);
	// Set Reset
	void setRST(bool data);

	void writeCommand8(uint8_t cmd);
	void writeCommand16(uint16_t cmd);
	void writeCommand32(uint32_t cmd);
	uint32_t writeCommandBuffer(uint8_t* buffer, uint32_t length);

	void writeData8(uint8_t data);
	void writeData16(uint16_t data);
	void writeData32(uint32_t data);
	uint32_t writeDataBuffer(uint8_t* buffer, uint32_t length);

protected:
	i2c_inst_t* _i2c;
	uint8_t _addr;
};

#endif // UMCDI_TRANSPORT_RP2040_HW_I2C