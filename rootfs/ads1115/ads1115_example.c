/*
 ============================================================================
 Name        : ads1115_example.c
 Author      : Giovanni Bauermeister
 Description : Read analog values from potentiometer using ADS1115 and prints to terminal
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "ads1115_rpi.h"

int main(void) {

	if(openI2CBus("/dev/i2c-2") == -1)
	{
		return EXIT_FAILURE;
	}
	setI2CSlave(0x48);
	while(1)
	{
		printf("Potenciometro = %.2f V  \n", readVoltage(0));
		sleep(1);
	}

	return EXIT_SUCCESS;
}
