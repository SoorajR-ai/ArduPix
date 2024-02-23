// Include the Ardumav library
#include "ardumav.h"

// Create an instance of the Ardumav class with Serial communication
Ardumav rover(&Serial);

// Coordinates of the Taj Mahal
bool GPS_update = true;               // Flag indicating GPS coordinates update
float Latitude = 27.17465353846637;   // Latitude of the Taj Mahal
float Longitude = 78.04207821615618;  // Longitude of the Taj Mahal
int heading = 30;                     // Initial heading direction

void setup() {
    // Initialize the serial communication with the computer
    Serial.begin(115200);
}

void loop() {
    // Run the Ardumav library logic
    rover.run();

    // Set the position of the rover with GPS coordinates and heading
    rover.SetPosition(GPS_update, Latitude, Longitude, heading);
}
