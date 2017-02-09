/*
  SD card basic file example
  https://www.arduino.cc/en/Reference/SD

 This example shows how to create and destroy an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - D7 - 13
 ** MISO - D6 - 12
 ** CLK  - D5 - 14
 ** CS   - D8 - 15

 SPI Ref: https://www.arduino.cc/en/Reference/SPI

 The ESP8266 has 2 SPI interfaces (called "SPI" and "HSPI" in the source code
 and the pin descriptions). The SPI register header file and the source code
 suggest that both interfaces have identical register sets, which are just
 located at different base addresses.
 */

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup ()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  Serial.print("Initializing SD card...");
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // Check if file exists
  if (SD.exists("example.txt"))
  {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // Open file for write
  myFile = SD.open("example.txt", FILE_WRITE);
  myFile.println("hello world");
  myFile.close();

  // Open file for read
  Serial.println("reading example.txt");
  myFile = SD.open("example.txt");
  if (myFile)
  {
    while (myFile.available())
    {
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else
  {
    Serial.println("error opening example.txt");
  }

  // Delete file
  Serial.println("Removing example.txt...");
  SD.remove("example.txt");

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }
}

void loop()
{
}
