
#include "ardumav.h"

Ardumav rover(&Serial);

void setup() {
    // Initialize the serial communication
    Serial.begin(115200);
}

void loop() {
    // Run the Ardumav library logic
    rover.run();
}
