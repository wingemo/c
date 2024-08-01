#include <stdio.h>
#include <wiringPi.h>
#include "sensor_interface.h"

int initializePins(PinConfig *pins) {
    if (wiringPiSetup() == -1) {
        return -1;
    }
    pinMode(pins->tempPin, INPUT);
    pinMode(pins->pressPin, INPUT);
    pinMode(pins->humidPin, INPUT);
    pinMode(pins->outputPin, OUTPUT);
    return 0;
}

SensorData readSensors(PinConfig *pins) {
    SensorData data = {0, 0, 0};
    data.tempReading = digitalRead(pins->tempPin);
    data.pressReading = digitalRead(pins->pressPin);
    data.humidReading = digitalRead(pins->humidPin);
    return data;
}

int sendOutput(PinConfig *pins, int result) {
    digitalWrite(pins->outputPin, result ? HIGH : LOW);
    return 0;
}

void cleanupPins(PinConfig *pins) {
    digitalWrite(pins->outputPin, LOW);
    
    pinMode(pins->tempPin, INPUT);
    pinMode(pins->pressPin, INPUT);
    pinMode(pins->humidPin, INPUT);
    pinMode(pins->outputPin, INPUT);  
}
