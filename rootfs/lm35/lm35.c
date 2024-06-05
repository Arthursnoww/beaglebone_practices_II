#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"

int main() {
    FILE* fp;
    char buffer[10];
    int adc_value;
    float temp_ant = 0.0;
    
	while(1){
	    fp = fopen(ADC_PATH, "r");
	    if (fp == NULL) {
		perror("Erro ao abrir o arquivo.");
		return 1;
	    }
	    fgets(buffer, sizeof(buffer), fp);
	    adc_value = atoi(buffer);
	    fclose(fp);
	    float celsius = adc_value/22.75;
	   	 printf("Temperatura: %.2fºC: \n", celsius);
	   	 
	   	 sleep(3);
    	}
}

