#include <sys/ioctl.h>
//#include "i2c-lcd.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SLAVE_ADDRESS_LCD 0x3f // change this according to ur setup
#define I2C_DEVICE_FILE_PATH	"/dev/i2c-2"
#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"

short lcd1602_write(uint8_t address, uint8_t *pData, uint8_t len);
short lcd1602_init(void);   // initialize lcd
void lcd1602_sendCommand(char command);  // send command to the lcd
void lcd1602_sendData(uint8_t data);  // send data to the lcd
void lcd1602_sendString(char *str);  // send string to the lcd
void lcd1602_setCursorPosition(bool row, int column);  // put cursor at the entered position row (0 or 1), col (0-15);
void lcd1602_clear(void);


/** Put this in the src folder **/

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

void led_blue(){
	int export_fd, period_fd, duty_cycle_fd, enable_fd;

    // Exportar o canal PWM
    export_fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);
    write(export_fd, "0", 1);
    close(export_fd);

    // Definir o período do sinal PWM
    period_fd = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY);
    write(period_fd, "1000000000", 10);
    close(period_fd);

    // Definir o ciclo de trabalho do sinal PWM
    duty_cycle_fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
    write(duty_cycle_fd, "500000000", 9);
    close(duty_cycle_fd);

    // Ativar o canal PWM
    enable_fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
    write(enable_fd, "1", 1);
    close(enable_fd);
}

int fd;

int row=0;
int col=0;

int main() {
	fd = open(I2C_DEVICE_FILE_PATH,O_RDWR);

    if ( fd < 0) {
        perror("Failed to open I2C device file.\n");
        return -1;
    }

    /*set the I2C slave address  */
    if (ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS_LCD) < 0) {
            perror("Failed to set I2C slave address.\n");
            close(fd);
            return -1;
    }

    lcd1602_init();

	FILE* fp;
    char buffer[10];
    int adc_value;
    float temp_ant = 0.0;
	float celsius; 
	char tempString[20];
    
	while(1){
	    fp = fopen(ADC_PATH, "r");
	    if (fp == NULL) {
		perror("Erro ao abrir o arquivo.");
		return 1;
	    }
	    fgets(buffer, sizeof(buffer), fp);
	    adc_value = atoi(buffer);
	    fclose(fp);
	    celsius = adc_value/22.75; 
        snprintf(tempString, sizeof(tempString), "%.2f C", celsius);
	   	sleep(1);
        lcd1602_setCursorPosition(0, 0);
        lcd1602_sendString("temperatura:");
        sleep(1);
		led_blue();
        /*lcd1602_setCursorPosition(1, 0);
        lcd1602_sendString("Teste definitivo");
        sleep(1);*/
	    //lcd1602_clear();
        lcd1602_setCursorPosition(2, 0);
        lcd1602_sendString(tempString);
        sleep(1);
		//lcd1602_clear();
        /*lcd1602_setCursorPosition(1, 0);
        lcd1602_sendString("UFC Quixada");
        sleep(1);
	sleep(100);*/
	}

	return 0;
}
