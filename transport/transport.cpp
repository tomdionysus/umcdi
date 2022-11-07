#include "transport.h"

void Transport ::writeCommand8(uint8_t cmd) {
	setDC(false);
	write8(cmd);
}

void Transport ::writeCommand16(uint16_t cmd) {
	setDC(false);
	write16(cmd);
}

void Transport ::writeCommand32(uint32_t cmd) {
	setDC(false);
	write32(cmd);
}

uint32_t Transport ::writeCommandBuffer(uint8_t* buffer, uint32_t length) {
	setDC(false);
	return writeBuffer(buffer, length);
}

void Transport ::writeData8(uint8_t data) {
	setDC(true);
	write8(data);
}

void Transport ::writeData16(uint16_t data) {
	setDC(true);
	write16(data);
}

void Transport ::writeData32(uint32_t data) {
	setDC(true);
	write32(data);
}

uint32_t Transport ::writeDataBuffer(uint8_t* buffer, uint32_t length) {
	setDC(false);
	return writeBuffer(buffer, length);
}
