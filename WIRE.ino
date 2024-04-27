#include <Wire.h> // Include the Wire library for I2C communication

void setup() {
  // Initialize the serial monitor at 9600 baud rate
  Serial.begin(9600);
  
  // Initialize I2C communication
  Wire.begin();
  
  // Print a message to the serial monitor indicating the scan is starting
  Serial.println("Scanning I2C bus...");
}

void loop() {
  // Loop through all possible I2C addresses (0 to 127)
  for (int address = 0; address <= 127; address++) {
    // Start the transmission to the current I2C address
    Wire.beginTransmission(address);
    
    // Check if the device at this address responds
    int error = Wire.endTransmission();
    
    // If there is no error (error code 0), a device is present at this address
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      // Print the address in hexadecimal format (two characters)
      Serial.print(address, HEX);
      Serial.println("  !");
    }
    // Delay for a short period to allow the bus to recover
    delay(1);
  }
  
  // Scan complete, print a message and wait before scanning again
  Serial.println("I2C scan complete.");
  delay(5000); // Wait for 5 seconds before scanning again
}
