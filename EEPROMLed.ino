#define I2Caddress 0x50
#include "Wire.h"
void writeEEPROM(int address, byte val, int i2c_address)
{
  // Begin transmission to I2C EEPROM
  Wire.beginTransmission(i2c_address);
 
  // Send memory address as two 8-bit bytes
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
 
  // Send data to be stored
  Wire.write(val);
 
  // End the transmission
  Wire.endTransmission();
 
  // Add 5ms delay for EEPROM
  delay(5);
}
 
// Function to read from EEPROM
byte readEEPROM(int address, int i2c_address)
{
  // Define byte for received data
  byte rcvData = 0xFF;
 
  // Begin transmission to I2C EEPROM
  Wire.beginTransmission(i2c_address);
 
  // Send memory address as two 8-bit bytes
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
 
  // End the transmission
  Wire.endTransmission();
 
  // Request one byte of data at current memory address
  Wire.requestFrom(i2c_address, 1);
 
  // Read the data and assign to variable
  rcvData =  Wire.read();
 
  // Return the data as function output
  return rcvData;
}
int address=0;
int led=13,but=12;
int Flag=0;
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(but, INPUT_PULLUP);
  if(readEEPROM(0, I2Caddress)==1)
  {
    Flag=1;
    digitalWrite(led,1);
  }
  if(readEEPROM(0, I2Caddress)==0)
  {
    Flag=0;
    digitalWrite(led,0); 
  }
}
void loop()
{
  int val=digitalRead(but);
  if(val==0)
  {
    if(Flag==0)
    {
      digitalWrite(led,1);
      Flag=1;
      writeEEPROM(0, 1, I2Caddress);
    }
    else if(Flag==1)
    {
      digitalWrite(led,0);
      Flag=0;
      writeEEPROM(0, 0, I2Caddress);
    }
  }
  Serial.println("Led State : "+String(Flag));
  delay(1000);
}
