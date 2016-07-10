#ifndef LCDT_OUT
#define     LCDT_OUT               GPIOB->ODR
#endif

// Connect RW leg to GND, and power supply rails to +5V and gnd
// Define symbolic LCD - MCU pin mappings
// We've set DATA PIN TO 4,5,6,7 for easy translation
#ifndef LCDT_PIN_RS
#define     LCDT_PIN_RS            GPIO_Pin_9          // RS
#define     LCDT_PIN_EN            GPIO_Pin_8          // EN
#define     LCDT_PIN_D7            GPIO_Pin_7          // LCDT_PIN_D4 << 3
#define     LCDT_PIN_D6            GPIO_Pin_6          // LCDT_PIN_D4 << 2
#define     LCDT_PIN_D5            GPIO_Pin_5          // LCDT_PIN_D4 << 1
#define     LCDT_PIN_D4            GPIO_Pin_4          // LCDT_PIN_D4
#endif

// TODO calculate somehow
#define MICROSECOND_DELAY 1
#define SEND_DELAY (37 * MICROSECOND_DELAY)
#define SEND_LONG_DELAY (1520 * MICROSECOND_DELAY)
#define INIT_DELAY (40000 * MICROSECOND_DELAY)

GPIO_InitTypeDef  GPIO_InitStructure;
#define     LCDT_PIN_MASK  ((LCDT_PIN_RS | LCDT_PIN_EN | LCDT_PIN_D7 | LCDT_PIN_D6 | LCDT_PIN_D5 | LCDT_PIN_D4))

#define     FALSE                 0
#define     TRUE                  1

void __delay() {
	volatile uint32_t tmpvar;
	for (tmpvar = SEND_DELAY; tmpvar != 0; tmpvar--);
}

void __longDelay() {
	volatile uint32_t tmpvar;
	for (tmpvar = SEND_LONG_DELAY; tmpvar != 0; tmpvar--);
}

void __initDelay() {
	volatile uint32_t tmpvar;
	for (tmpvar = INIT_DELAY; tmpvar != 0; tmpvar--);
}

void pulseLcd()
{
    LCDT_OUT &= ~LCDT_PIN_EN;
    __delay();
    LCDT_OUT |= LCDT_PIN_EN;
    __delay();
    LCDT_OUT &= (~LCDT_PIN_EN);
    __delay();
}

void sendByte(char byteToSend, int isData)
{
	uint16_t clear = (~LCDT_PIN_MASK);
	uint16_t dataBit = 0;
	if (isData == TRUE) {
		clear |= LCDT_PIN_RS;
		dataBit |= LCDT_PIN_RS;
	}

	// TODO: use LCDT_PIN_D4
    LCDT_OUT &= clear;
    LCDT_OUT |= (byteToSend & 0xF0) | dataBit;
    pulseLcd();

    LCDT_OUT &= clear;
    LCDT_OUT |= ((byteToSend & 0x0F) << 4) | dataBit;
    pulseLcd();
}

void cursor(char row, char col)
{
    char address;
    if (row == 0) {
        address = 0;
    } else {
        address = 0x40;
    }

    address |= col;
    sendByte(0x80 | address, FALSE);
    __longDelay();

#ifdef LCD_SEMIHOSTING
    SH_SendChar('\n');
    SH_SendChar('[');
    SH_SendChar('0' + row);
    SH_SendChar(',');
    SH_SendChar('0' + (col / 10));
    SH_SendChar('0' + (col % 10));
    SH_SendChar(']');
    SH_SendChar(':');
    SH_SendChar(' ');
#endif
}


void clearLcdScreen()
{
    sendByte(0x01, FALSE);
    __longDelay();
    sendByte(0x02, FALSE);
    __longDelay();
#ifdef LCD_SEMIHOSTING
    SH_SendChar('\n');
#endif
}

void initializeLcd(void)
{

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LCDT_PIN_MASK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    LCDT_OUT &= (~LCDT_PIN_MASK);
    __initDelay();

	// Send 3 times 8-bit mode and 1 time 4-bit mode
	sendByte(0b00110011, FALSE);
    sendByte(0b00110010, FALSE);

    // Init rest of settings in 4-bit mode
    sendByte(0b00101000, FALSE);
    sendByte(0b00001100, FALSE);
    sendByte(0b00000110, FALSE);

	clearLcdScreen();
}

void initChar(int c, uint8_t* tile)
{
    sendByte(0b01000000 | (c << 3), FALSE);
    for (int i = 0; i < 8; i++) {
        sendByte(*tile, TRUE);
        tile++;
    }
}

void printStr(char *text)
{
    char *c;
    c = text;
    while ((c != 0) && (*c != 0)) {
        sendByte(*c, TRUE);
#ifdef LCD_SEMIHOSTING
        SH_SendChar(*c);
#endif
        c++;
    }
}
