#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#define SLAVE_ADDRESS_LCD 0x27 // change this according to ur setup
#define I2C_DEVICE_FILE_PATH	"/dev/i2c-2"

short lcd1602_write(uint8_t address, uint8_t *pData, uint8_t len);
short lcd1602_init(void);   // initialize lcd
void lcd1602_sendCommand(char command);  // send command to the lcd
void lcd1602_sendData(uint8_t data);  // send data to the lcd
void lcd1602_sendString(char *str);  // send string to the lcd
void lcd1602_setCursorPosition(bool row, int column);  // put cursor at the entered position row (0 or 1), col (0-15);
void lcd1602_clear(void);