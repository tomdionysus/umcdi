#include "transport/RP2040_hw_spi.h"
#include "display/ST7735.h"

#define GPIO_CS 6
#define GPIO_DC 7
#define GPIO_RES 8

int main() {

	RP2040_hw_spi *tr = new RP2040_hw_spi();

	tr->init(0, 10000000, GPIO_DC, GPIO_RES);

	ST7735 *dp = new ST7735(tr, 80, 160);

	delete dp;
	delete tr;

}