#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#include <stdlib.h>

#include "stm32f4_discovery.h"

#include "lcd_text_display.h"
#include "lcd_microsprite.h"

int main(void)
{

	initializeLcd();

	uint8_t chars[8];
	chars[0] = 0b00011;
	chars[1] = 0b00111;
	chars[2] = 0b01101;
	chars[3] = 0b01111;
	chars[4] = 0b01011;
	chars[5] = 0b01100;
	chars[6] = 0b00111;
	chars[7] = 0b00011;
	initChar(6, &chars[0]);
	chars[0] = 0b11000;
	chars[1] = 0b11100;
	chars[2] = 0b10110;
	chars[3] = 0b11110;
	chars[4] = 0b11010;
	chars[5] = 0b00110;
	chars[6] = 0b11100;
	chars[7] = 0b11000;
	initChar(7, &chars[0]);

//	chars[0] = 0b10000001;
//	chars[1] = 0b01000010;
//	chars[2] = 0b00100100;
//	chars[3] = 0b00011000;
//	chars[4] = 0b00011000;
//	chars[5] = 0b00100100;
//	chars[6] = 0b01000010;
//	chars[7] = 0b10000001;

	chars[0] = 0b00111100;
	chars[1] = 0b01111110;
	chars[2] = 0b11011011;
	chars[3] = 0b11111111;
	chars[4] = 0b10111101;
	chars[5] = 0b11000011;
	chars[6] = 0b01111110;
	chars[7] = 0b00111100;

	cursor(0,0);
	printStr("16x2 demo \x06\x07 \x06\x07 ");
	cursor(1,0);
	printStr(" \x06\x07 Press button");

	initLeds(LEDS_ALL);
	initButton();

	uint8_t cnt = 0;
    while(1)
    {
    	ledsOn(LED_R);
    	if (isButtonPressed()) {
        	ledsOn(LED_G);

        	clearLcdScreen();

			drawSprite(0, cnt % 120, 6, &chars[0]);
//			__initDelay();
//			__initDelay();

			char s[17];
			s[16] = 0;

			cursor(0,0);
			itoa(cnt, s, 10);
        	printStr("Pos: ");
			printStr(&s[0]);

			cursor(1,0);
			for (int i = 0; i < 16; i++) {
				s[i] = cnt + i;
				if (s[i] == 0) s[i] = ' ';
			}
			printStr(&s[0]);

			cnt++;
    	} else {
        	ledsOff(LED_G);
    	}

    }
}
