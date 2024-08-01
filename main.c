#include <unistd.h>  // For sleep()
#include "sensor_interface.h"

const int SENSOR_THRESHOLD = 2;

int initialize(PinConfig *pins) {
    return initializePins(pins);
}

int evaluateSensorInput(SensorData data) {
    int activeSensorCount = (data.tempReading > 0) +
                            (data.pressReading > 0) +
                            (data.humidReading > 0);
    return activeSensorCount >= SENSOR_THRESHOLD;
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
