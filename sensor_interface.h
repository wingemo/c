#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include <wiringPi.h>

typedef struct {
    int tempPin;
    int pressPin;
    int humidPin;
    int outputPin;
} PinConfig;

typedef struct {
    int tempReading;
    int pressReading;
    int humidReading;
} SensorData;

int initializePins(PinConfig *pins);
SensorData readSensors(PinConfig *pins);
int sendOutput(PinConfig *pins, int result);

#endif // SENSOR_INTERFACE_H
