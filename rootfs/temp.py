import Adafruit_BBIO.ADC as ADC

import time

sensor = "P9_40"

ADC.setup(sensor)

while True:
    temperature = (float(ADC.read_raw(sensor))*4096)/1800
    Celsius = (temperature)/22.75
    fahrenheit = (Celsius * 9/5) + 32
    print("tempo em celsius: %d , tempo em Fahreinheit: %d")
    time.sleep(1)