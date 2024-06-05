import Adafruit_BBIO.ADC as ADC
 
import time
 
Sensor = "P9_40"
 
ADC.setup(Sensor)
 
while True:
 
        Temperature = (float(ADC.read_raw(Sensor))*4096)/1800
 
        Celsius = (Temperature)/22.75
 
        Fahrenheit = (Celsius * 9/5) + 32
        print('Temp in C: %dnTemp in F: %dn'%(Celsius , Fahrenheit))
 
        time.sleep(1)
 

###
