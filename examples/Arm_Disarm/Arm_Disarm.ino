// Include the Ardumav library
#include "ardumav.h"

// Create an instance of the Ardumav class with Serial communication
Ardumav rover(&Serial);

// Define a pin for the Arm Status LED
int Arm_Status_LEDPin = 13;

void setup() {
    // Initialize the serial communication with the computer
    Serial.begin(115200);
    
    // Set the Arm Status LED pin as an output
    pinMode(Arm_Status_LEDPin, OUTPUT);
}

void loop() {
    // Run the Ardumav library logic
    rover.run();

    // Get the Arm Status from Ardumav
    uint8_t Arm_Status = rover.GetArmStatus();

    // Control the Arm Status LED based on the Arm Status
    if (Arm_Status) {
        digitalWrite(Arm_Status_LEDPin, HIGH);  // Turn on the LED if armed
    } else {
        digitalWrite(Arm_Status_LEDPin, LOW);   // Turn off the LED if disarmed
    }
}
