#include "transport/RP2040_hw_spi.h"
#include "display/ST7735.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"


#define GPIO_RES 21
#define GPIO_DC 20

#define GPIO_ALIVE 15

int main() {

    gpio_init(GPIO_ALIVE);
    gpio_set_dir(GPIO_ALIVE, GPIO_OUT);

    for(uint8_t i= 0; i<3; i++) { 
		gpio_put(GPIO_ALIVE,0);
		sleep_ms(150);
		gpio_put(GPIO_ALIVE,1);
		sleep_ms(150);
	}

	RP2040_hw_spi *tr = new RP2040_hw_spi();

	tr->init(0, 10000000, GPIO_DC, GPIO_RES);

	ST7735 *dp = new ST7735(tr, 80, 160);

	dp->init();
	dp->fillScreen(0xFFFF00);

	delete dp;
	delete tr;

}