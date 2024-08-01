// sensor_evaluation.c
#include "sensor_evaluation.h"

const int SENSOR_THRESHOLD = 2;

int evaluateSensorInput(SensorData data) {
    int activeSensorCount = (data.tempReading > 0) +
                            (data.pressReading > 0) +
                            (data.humidReading > 0);
    return activeSensorCount >= SENSOR_THRESHOLD;
}
