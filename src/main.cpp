/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | twitter.com/pixeledi
REYAX Bluetooth module with ATtiny | V1.0 | 05/2023
*/

#include <Arduino.h>
#include <SoftwareSerial.h> //Software Serial Port
#include <Wire.h>

#define DEBUG_ENABLED 1

SoftwareSerial BTserial(3, 4); // RX, TX
String BTData = "";
String prevBTData = "";
byte relais = 1;
bool RelaisOn = false;

void setup()
{
  BTserial.begin(9600);
  pinMode(relais, OUTPUT);
}

void loop()
{
  if (BTserial.available())
  {
    String BTData2 = BTserial.readStringUntil('\n');
    // process Message which we get in this format: +RCV=1,9,mymessage
    int length = BTData2.length();
    String lastDigit = BTData2.substring(length - 2);
    lastDigit.trim();

    // received message 1 or 0 
    // Set Flag according the value
    if (lastDigit == "1")
    {
      RelaisOn = true;
    }
    else if (lastDigit == "0")
    {
      RelaisOn = false;
    }
  }


  if (RelaisOn)
  {
    digitalWrite(relais, HIGH);
  }
  else
  {
    digitalWrite(relais, LOW);
  }
}