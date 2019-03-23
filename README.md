# ArduinoOneWire
With this sketch, you can write and read the 8-byte code in the key RW1990. To change the code being written, in the sketch you need to replace the data in the variable "ID" with the ones you need.
## How to use

1. Install the library in ArduinoIDE from https://github.com/PaulStoffregen/OneWire
2. Open the ArduinoOneWire.ino sketch in the Arduino
3. We assemble the scheme according to the image ![scheme](https://github.com/minbbb/ArduinoOneWire/blob/master/scheme.jpeg)
4. Open the serial monitor
5. To read the key id, send the symbol "r" through the serial monitor and close the contacts to the key
6. To write the id to the key, send the symbol "w" through the serial monitor and close the contacts to the key