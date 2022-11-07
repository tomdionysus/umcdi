#include <stdint.h>

using namespace std;

// A Transport is an IO interface over which a Display is driven. The transport may be an SPI device on a particular microcontroller or platform.
class Transport {

public:
	Transport();
	~Transport();

	// Init/Shutdown. Should be overridden for each transport.
	virtual void init();
	virtual void shutdown();

	// Read 8/16/32 bits
	virtual uint8_t read8();
	virtual uint16_t read16();
	virtual uint32_t read32();

	// Write 8/16/32 bits
	virtual void write8(uint8_t data);
	virtual void write16(uint16_t data);
	virtual void write32(uint32_t data);

	// Read into a buffer, up to length bytes. Return no. of read bytes
	virtual uint32_t readBuffer(uint8_t* buffer, uint32_t length);
	// Write from a buffer, length bytes. Return no. of written bytes
	virtual uint32_t writeBuffer(uint8_t* buffer, uint32_t length);

	// Set Data/Control
	virtual void setDC(bool data);
	// Set Reset
	virtual void setRST(bool data);

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
};