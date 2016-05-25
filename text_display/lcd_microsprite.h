
void drawSprite(int row, int x, int c, uint8_t* sprite) {
	int col1 = x / 6 - 2;
	int bitOffset = x % 6;
	// move to pos1
	cursor(row, col1 - 1);
	sendByte(' ', TRUE);

	sendByte(' ', TRUE);
    sendByte(0b01000000 | (c << 3), FALSE);
    uint8_t* spr = sprite;
    for (int i = 0; i < 8; i++) {
    	uint8_t s = ((*spr) >> (2 + bitOffset)) & 0b11111;
    	sendByte(s, TRUE);
    	spr++;
    }
	cursor(row, col1);
	sendByte(c, TRUE);

	sendByte(' ', TRUE);
    sendByte(0b01000000 | ((c + 1) << 3), FALSE);
    spr = sprite;
    for (int i = 0; i < 8; i++) {
    	uint8_t s = ((*spr) << (6 - bitOffset) >> 2) & 0b11111;
    	sendByte(s, TRUE);
    	spr++;
    }
	cursor(row, col1 + 1);
	sendByte(c + 1, TRUE);
}
