#include <stdio.h>
#include <unistd.h>  // För sleep()
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

const int SENSOR_THRESHOLD = 2;

int initialize(PinConfig pins) {
    return initializePins(pins);
}

SensorData readSensors(PinConfig pins) {
    SensorData data = {0, 0, 0};
    data.tempReading = digitalRead(pins.tempPin);
    data.pressReading = digitalRead(pins.pressPin);
    data.humidReading = digitalRead(pins.humidPin);
    return data;
}

int evaluateSensorInput(SensorData data) {
    int activeSensorCount = (data.tempReading > 0) +
                            (data.pressReading > 0) +
                            (data.humidReading > 0);
    return activeSensorCount >= SENSOR_THRESHOLD;
}

int sendOutput(PinConfig pins, int result) {
    digitalWrite(pins.outputPin, result ? HIGH : LOW);
    return 0;
}

int execute(PinConfig pins) {
    SensorData data = readSensors(pins);
    if (data.tempReading == -1 || data.pressReading == -1 || data.humidReading == -1) {
        fprintf(stderr, "Failed to read sensor data\n");
        return -1;
    }

    int result = evaluateSensorInput(data);
    if (sendOutput(pins, result) != 0) {
        fprintf(stderr, "Failed to send output\n");
        return -1;
    }

    return 0;
}

int main() {
    PinConfig pins = {
        .tempPin = 0,
        .pressPin = 1,
        .humidPin = 2,
        .outputPin = 3
    };

    if (initialize(pins) != 0) {
        return 1;
    }

    if (execute(pins) != 0) {
        fprintf(stderr, "Execution failed\n");
        return 1;
    }

    return 0;
}
