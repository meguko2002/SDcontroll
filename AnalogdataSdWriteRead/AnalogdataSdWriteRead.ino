/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 5;     // select the pin for the LED


void setup() {
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  SD.remove("datalog.txt");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = 0;  // variable to store the value coming from the sensor
  int outputValue = 0;        // value output to the PWM (analog out)

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    for (int i = 0; i < 1000; i++) {
      sensorValue = analogRead(sensorPin);
      outputValue = map(sensorValue, 0, 1023, 0, 255);
      analogWrite(ledPin, outputValue);
      dataFile.write(outputValue);

      Serial.println(String(outputValue));
      delay(10);
    }
    dataFile.close();
  }

  Serial.println("Read datalog.txt");
  dataFile = SD.open("datalog.txt");
  if (dataFile) {
    while (dataFile.available()) {
      outputValue = dataFile.read();
      analogWrite(ledPin, outputValue);
      Serial.println(outputValue);
      delay(10);
    }
    dataFile.close();
  }
  while (1) {}
}









