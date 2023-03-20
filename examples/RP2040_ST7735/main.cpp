#include "RP2040_hw_spi.h"
#include "ST7735.h"

#define GPIO_SCL 	10
#define GPIO_SDA 	11
#define GPIO_CS  	13
#define GPIO_DC  	14
#define GPIO_RST 	15

#define SPI_CLK_FREQ    30 * 1024 * 1024

int main() {

	RP2040_hw_spi *transport = new RP2040_hw_spi();
	transport->init(1, SPI_CLK_FREQ, GPIO_DC, GPIO_RST, GPIO_CS, GPIO_SCL, GPIO_SDA);

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