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
const int INTERVAL = 60;  // Intervallet i sekunder

int initialize(PinConfig *pins) {
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "WiringPi setup failed!\n");
        return -1;
    }
    pinMode(pins->tempPin, INPUT);
    pinMode(pins->pressPin, INPUT);
    pinMode(pins->humidPin, INPUT);
    pinMode(pins->outputPin, OUTPUT);
    return 0;
}

void readSensors(const PinConfig *pins, SensorData *data) {
    data->tempReading = digitalRead(pins->tempPin);
    data->pressReading = digitalRead(pins->pressPin);
    data->humidReading = digitalRead(pins->humidPin);
}

int evaluateSensorInput(const SensorData *data) {
    int activeSensorCount = (data->tempReading > 0) +
                            (data->pressReading > 0) +
                            (data->humidReading > 0);
    return activeSensorCount >= SENSOR_THRESHOLD;
}

void sendOutput(PinConfig *pins, int result) {
    digitalWrite(pins->outputPin, result ? HIGH : LOW);
}

int main() {
    PinConfig pins = {
        .tempPin = 0,
        .pressPin = 1,
        .humidPin = 2,
        .outputPin = 3
    };
    SensorData data;

    if (initialize(&pins) != 0) {
        return 1;
    }

    while (1) {
        readSensors(&pins, &data);
        sendOutput(&pins, evaluateSensorInput(&data));
        sleep(INTERVAL);  // Vänta i 60 sekunder
    }

    return 0;  // Denna rad kommer aldrig att nås på grund av den oändliga loopen
}
