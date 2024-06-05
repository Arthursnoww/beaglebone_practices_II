
/** Put this in the src folder **/

#include "i2c-lcd.h"

#define LCD_CLEAR_DISPLAY 			0x01
#define LCD_RETURN_HOME   			0x02
#define LCD_ENTRY_MODE_SET 			0x04
#define LCD_DISPLAY_CONTROL			0x08
#define LCD_CURSOR_OR_DISPLAY_SHIFT 0x10
#define LCD_FUNCTION_SET 			0x20
#define LCD_SET_CGRAM_ADDRESS 		0x40
#define LCD_SET_DDRAM_ADDRESS 		0x80
/*entry mode settings*/
#define LCD_ENTRY_MODE_SH 			0x01
#define LCD_ENTRY_MODE_ID			0x02
/*display on/off control settings*/
#define LCD_BLINK_ON 				0x01
#define LCD_CURSOR_ON 				0x02
#define LCD_DISPLAY_ON 				0x04
/*cursor or display shift settings*/
#define LCD_CURSOR_SHIFT_RIGHT 		0x04
#define LCD_CURSOR_SHIFT_LEFT 		0x00
#define LCD_DISPLAY_SHIFT_ON 		0x08
#define LCD_DISPLAY_SHIFT_OFF 		0x00
/*function settings*/
#define LCD_FUNCTION_F_5X11 		0x04//5x11 dots format display mode
#define LCD_FUNCTION_F_5X08 		0x00//5x8 dots format display mode
#define LCD_FUNCTION_N_1LANE 		0x00//1-display mode is set
#define LCD_FUNCTION_N_2LANE 		0x08//2-line display mode is set
#define LCD_FUNCTION_DL_4BIT 		0x00//4 bit bus mode
#define LCD_FUCNTION_DL_8BIT 		0x10//8 bit bus mode
/*lcd control bits*/
#define LCD_RS        			(1 << 0)
#define LCD_RW        			(1 << 1)
#define LCD_EN        			(1 << 2)
#define LCD_BACK_LIGHT  		(1 << 3)
int fd;

short lcd1602_write(uint8_t address, uint8_t *pData, uint8_t len) {
	int ret;
	char buf[len+1];
	buf[0] = address;
	for(int i=1; i < (len+1); i++) {
		buf[i] =  *(pData+(i-1) );
	}

	ret = write(fd,buf,(len+2));
	if( ret <= 0) {
		perror("Write failed/n");
		return -1;
	}

	return 0;
}


void lcd1602_sendCommand(char command) {
	const char commandBit4To7 = (command&0xf0);
	const char commandBit0To3 = (0xF0 & (command<<4));
	uint8_t commandBuf[4];
	commandBuf[0] = commandBit4To7 | LCD_EN | LCD_BACK_LIGHT;
	commandBuf[1] = commandBit4To7 | LCD_BACK_LIGHT;
	commandBuf[2] = commandBit0To3 | LCD_EN | LCD_BACK_LIGHT;
	commandBuf[3] = commandBit0To3 | LCD_BACK_LIGHT;
	lcd1602_write(SLAVE_ADDRESS_LCD, (uint8_t *)commandBuf, 4);
}

void lcd1602_sendData(uint8_t data) {
	const uint8_t dataBit4To7 = (0xF0 & data);
	const uint8_t dataBit0To3 = (0xF0 & (data<<4));
	uint8_t dataBuf[4];
	dataBuf[0] = dataBit4To7|LCD_EN | LCD_BACK_LIGHT | LCD_RS;
	dataBuf[1] = dataBit4To7|LCD_BACK_LIGHT | LCD_RS;
	dataBuf[2] = dataBit0To3|LCD_EN | LCD_BACK_LIGHT | LCD_RS;
	dataBuf[3] = dataBit0To3|LCD_BACK_LIGHT | LCD_RS;
	lcd1602_write(SLAVE_ADDRESS_LCD, (uint8_t *)dataBuf, 4);
}

void lcd1602_clear(void) {
	lcd1602_sendCommand(0x80);
	for (int i=0; i<70; i++)
	{
		lcd1602_sendData(' ');
	}
}

void lcd1602_setCursorPosition(bool row, int column) {
    switch (row)
    {
        case 0:
        	column |= 0x80;
            break;
        case 1:
        	column |= 0xC0;
            break;
    }

    lcd1602_sendCommand(column);
}


short lcd1602_init (void) {
    //dislay initialisation
	lcd1602_sendCommand(LCD_FUNCTION_SET | LCD_FUNCTION_DL_4BIT | LCD_FUNCTION_N_2LANE | LCD_FUNCTION_F_5X08);
	usleep(1000);
	lcd1602_sendCommand(LCD_DISPLAY_CONTROL ); //Display on/off control --> D=0,C=0, B=0  ---> display off
	usleep(1000);
	lcd1602_sendCommand(LCD_CLEAR_DISPLAY);  // clear display
	usleep(1000);
	lcd1602_sendCommand(LCD_ENTRY_MODE_SET | LCD_ENTRY_MODE_ID); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	usleep(1000);
	lcd1602_sendCommand(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)

	return 0;
}

void lcd1602_sendString(char *str) {
	while (*str) {
		lcd1602_sendData(*str++);
	}
}
