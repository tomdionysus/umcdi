#include "BCM2835_hw_spi.h"
#include "ST7735.h"

#include <bcm2835.h>
#include <stdio.h>

#define GPIO_CS  	10
#define GPIO_SDA 	12
#define GPIO_SCL 	14
#define GPIO_RST 	0
#define GPIO_DC  	2

#define SPI_CLK_DIVIDER 4

int main() {

	printf("BCM2835/ST7735 Display Driver Example\n");

	BCM2835_hw_spi *transport = new BCM2835_hw_spi();
	transport->init(SPI_CLK_DIVIDER, GPIO_DC, GPIO_RST, GPIO_CS);

	ST7735 *display = new ST7735(transport, 160, 80, 2);
	display->init();

	while(1) {
		display->fillScreen(0xFF0000);
		transport->delay_ms(2000);
		display->fillScreen(0x00FF00);
		transport->delay_ms(2000);
		display->fillScreen(0x0000FF);
		transport->delay_ms(2000);
		display->fillScreen(0xFFFF00);
		transport->delay_ms(2000);
		display->fillScreen(0x00FFFF);
		transport->delay_ms(2000);
		display->fillScreen(0xFFFFFF);
		transport->delay_ms(2000);
		display->fillScreen(0x000000);
		transport->delay_ms(2000);
	}

	transport->shutdown();

	delete display;
	delete transport;

}