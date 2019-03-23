#include <OneWire.h>
#define pin 10

byte ID[8] = {0x9B, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01};
OneWire ibutton(pin);
byte arr[8];
char command = 0;

void setup(){
	Serial.begin(9600);
}

void loop(){
	if (!ibutton.search(arr)){
		ibutton.reset_search();
		delay(200);
		return;
	}
	command = Serial.read();
	if (command == 'r'){ //Read
		delay(200);
		Serial.print("ID: ");
		for (signed char x = 7; x >= 0; x--){
			Serial.print(arr[x], HEX); 
			Serial.print(" ");
		}
		byte crc;
		crc = ibutton.crc8(arr, 7);
		if(crc == arr[7]){
			Serial.println("- CRC correct");
		}else{
			Serial.print("- CRC is incorrect. Correct CRC is '");
			Serial.print(crc, HEX);
			Serial.println("'");
		}
		command = 0;
	}
	if (command == 'w'){ //Write
		delay (200);
		ibutton.skip();
		ibutton.reset();
		ibutton.write(0x33);
		Serial.print("ID before write: ");
		byte tempArr[8];
		for (signed char x = 7; x >= 0; x--){
			tempArr[x] = ibutton.read();
		}
		for (signed char x = 0; x <= 7; x++){
			Serial.print(tempArr[x], HEX);
			Serial.print(" ");
		}
		ibutton.skip();
		ibutton.reset();
		ibutton.write(0xD1);
		digitalWrite(10, LOW);
		pinMode(10, OUTPUT);
		delayMicroseconds(60);
		pinMode(10, INPUT);
		digitalWrite(10, HIGH);
		delay(10);
		Serial.println();
		Serial.print("Writing iButton ID: ");
		for (byte x = 0; x < 8; x++){
			Serial.print(ID[x],HEX);
			Serial.print(" ");
		}
		Serial.println();
		ibutton.skip();
		ibutton.reset();
		ibutton.write(0xD5);
		for (signed char x = 7; x >= 0; x--){
			writeByte(ID[x]);
			Serial.print("*");
		}
		Serial.println();
		ibutton.reset();
		ibutton.write(0xD1);
		digitalWrite(10, LOW);
		pinMode(10, OUTPUT);
		delayMicroseconds(10);
		pinMode(10, INPUT);
		digitalWrite(10, HIGH);
		delay(10);
		command = 0;
	}
}

int writeByte(byte data){
	int data_bit;
	for (data_bit = 0; data_bit < 8; data_bit++){
		if (data & 1){
			digitalWrite(pin, LOW);
			pinMode(pin, OUTPUT);
			delayMicroseconds(60);
			pinMode(pin, INPUT);
			digitalWrite(pin, HIGH);
			delay(10);
		}
		else {
			digitalWrite(pin, LOW);
			pinMode(pin, OUTPUT);
			pinMode(pin, INPUT);
			digitalWrite(pin, HIGH);
			delay(10);
		}
		data = data >> 1;
	}
	return 0;
}
