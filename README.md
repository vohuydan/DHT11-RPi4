# DHT11-RPi4
Library to use DHT11 with the Raspberry Pi 4.<br>
The purpose of this project was to explore the abilities of the Raspberry Pi 4 board as well as practice writing  a simple OOP C++ code.<br>
9/5/2022<br>

# Abstract
This is a simple library that works with the Raspberry Pi 4 and the DHT11 sensor. The Raspberry Pi gets requests data every 10 seconds and stores the data into a .csv file. 


![image](https://user-images.githubusercontent.com/77210680/189565756-02536377-28d6-4591-82d4-c4d1c38d0c4a.png)


# Materials
Raspbery Pi 4 or equivalent<br>
DHT11 Sensor<br>
3 Jumper wires<br>

# Configuration and Installation

Depending on the DHT11 module used, the configuration is relatively the same. Connect the power of the sensor to a 3.3V GPIO pin, the Ground pin to any ground GPIO pin, and the signal to any available GPIO pin. If using a 4 pin DHT11, remember to connect a 4.7k or 10k ohm resistor between the signal and 3.3V pins.

This project uses wiringPi. The following code will install wiringPi:

```console
$ git https://github.com/WiringPi/WiringPi.git
```

There are 3 files in this repository: DHT11.cpp, DHT11.h and main.cpp. To clone the repo, run the following code:

``` console
$ git clone https://github.com/vohuydan/DHT11-RPi4.git
```

Once downloaded run the following code to compile and execute the project:

```console
$ g++ -c DHT11.cpp - o DHT11.o -l wiringPi
$ g++ main.cpp DHT11.o -l wiringPi -o DHT11Test
$ ./DHT11Test
```

# Introduction
The DHT11 is a relatively cheap humidity and temperature sensor that can be used for any IoT or electronics project. Using a single wire serial interface (Note: different from 1-wire), the DHT11 sends 5 bytes of binary data to the microcontroller, where the first and second byte are the integral and decimal humidity value, the third and fourth byte are the integral and decimal temperature value. The fifth byte is the checksum value which verifies that the previous four bytes of data are valid. A valid checksum should be equal to the sum of the first 4 bytes, the easiest way to do this is converting the binary data to decimal value. An example of the data is provided below.


|   |(I)Humidity|(D)Humidity|(I)Temperature|(D)Temperature|Checksum|
|--------|--------|--------|--------|--------|--------|
|Binary|0100 0010|0000 0000|0001 0101|0000 0100|1110 1011|
|Decimal|66|0|21|4|91|



|Byte|Binary|Decimal|
|---|---|---|
|(I)Humidity|0100 0010|66|
|(D)Humidity|0000 0000|0|
|(I)Temperature|0001 0101|21|
|(D)Temperature|0000 0100|4|
|Checksum|(1)1110 1011|91|

|Humidity| Temperature (c)|
|---|---|
|66%|21.4|


# Operation

Since the DHT11 uses a single wire, the Raspberry Pi starts communication by sending the sensor a low pulse and then holds a high pulse. The sensor responds by pulling the pin low and then pulling the pin high. Following the high voltage, the sensor starts sending the data. 
![image](https://user-images.githubusercontent.com/77210680/189565217-e14d9cf6-0821-47a4-8f12-d0b111248889.png)


In one "bit" signal, the sensor pulls the sensor low for about 50 us and then pulls up for 28us-70us. The length of the high voltage determines if the bit data is a 0 or a 1.

![image](https://user-images.githubusercontent.com/77210680/189565287-bebef281-bc9b-43df-8538-4e627be5b635.png)

![image](https://user-images.githubusercontent.com/77210680/189565322-8abbae9f-de22-4ff4-bd25-530bf7b3080c.png)


# Code

This project is setup to run continuously and print/store data every 10 seconds.  There are a few things that can be modified in the main.cpp and DHT11.cpp.




# Conclusion

This library is a great tool to learn how to use the DHT11, basics of using C++ classes, as well as simple commands to compile and execute the program in the console. The DHT11 is overall dependendable for providing tmperature and humidity, however there are several inconsistencies that came up while writing this library. First off, the expected response from the sensor during data transmission should be a 50us low voltage pulse followed by a 28us or 70us high voltage pulse, but using the uinstd.h library to keep track of the pulses, the 50us low pulse is closer to 25us.

![image](https://user-images.githubusercontent.com/77210680/189565166-04c75965-6b0d-4534-b40d-957cdb3e6055.png)


Secondly, the DHT11 is inconsistent and checksum is not always valid during the first time data is transmitted. This is a common problem with the DHT11 sensors as well as other relatively affordable prototyping sensors. There are no way to mitigate this. Some solutions are to try to test muktiple DHT11s to find one that is more consistent or try an alternative sensor to read humidity and temperature.



# Reference
https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf 
