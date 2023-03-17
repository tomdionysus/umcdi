#include <stdexcept>

using namespace std;

#ifndef UMCDI_TRANSPORT
#define UMCDI_TRANSPORT

// A Transport is an IO interface over which a Display is driven. The transport may be an SPI device on a particular microcontroller or platform.
class Transport {

public:
	Transport();
	~Transport();

	// Read 8/16/32 bits
	virtual uint8_t read8() = 0;
	virtual uint16_t read16() = 0;
	virtual uint32_t read32() = 0;

	// Write 8/16/32 bits
	virtual void write8(uint8_t data) = 0;
	virtual void write16(uint16_t data) = 0;
	virtual void write32(uint32_t data) = 0;

	virtual void delay_ms(uint32_t ms) = 0;

	// Read into a buffer, up to length bytes. Return no. of read bytes
	virtual uint32_t readBuffer(uint8_t* buffer, uint32_t length) = 0;
	// Write from a buffer, length bytes. Return no. of written bytes
	virtual uint32_t writeBuffer(uint8_t* buffer, uint32_t length) = 0;

	// Set Data/Control
	virtual void setDC(bool data) = 0;
	// Set Reset
	virtual void setRST(bool data) = 0;

	void writeCommand8(uint8_t cmd);
	void writeCommand16(uint16_t cmd);
	void writeCommand32(uint32_t cmd);
	uint32_t writeCommandBuffer(uint8_t* buffer, uint32_t length);

	void writeData8(uint8_t data);
	void writeData16(uint16_t data);
	void writeData32(uint32_t data);
	uint32_t writeDataBuffer(uint8_t* buffer, uint32_t length);

protected:
	uint8_t _rst;
	uint8_t _dc;
	uint8_t _cs;
};

#endif // UMCDI_TRANSPORT