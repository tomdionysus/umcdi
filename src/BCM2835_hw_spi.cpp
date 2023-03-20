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

void BCM2835_hw_spi ::init(uint16_t clockDivider, uint8_t gpio_dc, uint8_t gpio_rst, uint8_t gpio_cs) {
	// Save which GPIO pins have these functions
	_dc = gpio_dc;
	_rst = gpio_rst;

	// Init GPIO
    bcm2835_gpio_fsel(_dc, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(_rst, BCM2835_GPIO_FSEL_OUTP);

    // Init SPI
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(clockDivider); 
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
}

void BCM2835_hw_spi ::shutdown() {
	bcm2835_spi_end();
}

uint8_t BCM2835_hw_spi ::read8() {
	// throw std::runtime_error("Not Implemented");
	return 0;
}
uint16_t BCM2835_hw_spi ::read16() {
	// throw std::runtime_error("Not Implemented");
	return 0;
}
uint32_t BCM2835_hw_spi ::read32() {
	// throw std::runtime_error("Not Implemented");
	return 0;
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

void BCM2835_hw_spi ::delay_ms(uint32_t ms) {
	bcm2835_delay(ms);
}

uint32_t BCM2835_hw_spi ::readBuffer(uint8_t* buffer, uint32_t length) {
	// throw std::runtime_error("Not Implemented");
	return 0;
}

uint32_t BCM2835_hw_spi ::writeBuffer(uint8_t* buffer, uint32_t length) {
	bcm2835_spi_writenb((char*)buffer, length);
	return length;
}

void BCM2835_hw_spi ::setDC(bool data)
{
	bcm2835_gpio_write(_dc, data ? HIGH : LOW);
}

void BCM2835_hw_spi ::setRST(bool data)
{
	bcm2835_gpio_write(_rst, data ? HIGH : LOW);
}

void BCM2835_hw_spi ::setCS(bool data)
{
	// BCM2835 activates CS automatically on I/O
}
