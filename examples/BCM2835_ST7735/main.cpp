#include "RP2040_hw_spi.h"
#include "ST7735.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"


#define GPIO_SCL 	10
#define GPIO_SDA 	11
#define GPIO_CS  	13
#define GPIO_DC  	14
#define GPIO_RST 	15

#define SPI_CLK_FREQ    (30 * MHZ)

#define GPIO_ALIVE  16

int main() {

    gpio_init(GPIO_ALIVE);
    gpio_set_dir(GPIO_ALIVE, GPIO_OUT);

	gpio_put(GPIO_ALIVE,0);
	sleep_ms(1000);
	gpio_put(GPIO_ALIVE,1);
	sleep_ms(1000);

	RP2040_hw_spi *transport = new RP2040_hw_spi();
	transport->init(1, SPI_CLK_FREQ, GPIO_DC, GPIO_RST, GPIO_CS, GPIO_SCL, GPIO_SDA);

	ST7735 *display = new ST7735(transport, 160, 80, 2);
	display->init();

    for(uint8_t i= 0; i<3; i++) { 
		gpio_put(GPIO_ALIVE,0);
		sleep_ms(100);
		gpio_put(GPIO_ALIVE,1);
		sleep_ms(100);
	}

	while(1) {
		gpio_put(GPIO_ALIVE,0);
		display->fillScreen(0xFF0000);
		sleep_ms(2000);
		gpio_put(GPIO_ALIVE,1);
		display->fillScreen(0x00FF00);
		sleep_ms(2000);
		display->fillScreen(0x0000FF);
		sleep_ms(2000);
		display->fillScreen(0xFFFF00);
		sleep_ms(2000);
		display->fillScreen(0x00FFFF);
		sleep_ms(2000);
		display->fillScreen(0xFFFFFF);
		sleep_ms(2000);
		display->fillScreen(0x000000);
		sleep_ms(2000);
	}

	transport->shutdown();

	delete display;
	delete transport;

}