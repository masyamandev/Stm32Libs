
#define LED_R GPIO_Pin_14
#define LED_G GPIO_Pin_12
#define LED_B GPIO_Pin_15
#define LED_O GPIO_Pin_13
#define LEDS_ALL (LED_R | LED_G | LED_B | LED_O)
//#define LED_R LED_R
#define LED_L LED_G
#define LED_U LED_O
#define LED_D LED_B

#define USR_BTN GPIO_Pin_0

void initLeds(uint16_t leds);
void initButton();

#define ledsOn(leds) (GPIO_SetBits(GPIOD, leds))
#define ledsOff(leds) (GPIO_ResetBits(GPIOD, leds))

#define isButtonPressed() (GPIO_ReadInputDataBit(GPIOA, USR_BTN))

