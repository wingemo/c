// main.c
#include <unistd.h>  // For sleep()
#include "sensor_interface.h"
#include "sensor_evaluation.h"

int initialize(PinConfig *pins) {
    return initializePins(pins);
}

int execute(PinConfig *pins) {
    SensorData data = readSensors(pins);
    if (data.tempReading == -1 || data.pressReading == -1 || data.humidReading == -1) {
        return -1;
    }
    return sendOutput(pins, evaluateSensorInput(data));
}

int main() {
    PinConfig pins = {
        .tempPin = 0,
        .pressPin = 1,
        .humidPin = 2,
        .outputPin = 3
    };

    if (initialize(&pins) != 0) {
        return 1;
    }

    if (execute(&pins) != 0) {
        return 1;
    }

    return 0;
}
