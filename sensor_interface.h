/**
 * @file sensor_interface.h
 * @brief Provides definitions and prototypes for sensor interfacing functions.
 * 
 * This header file defines the data structures and function prototypes used for
 * interfacing with sensors connected to GPIO pins on a Raspberry Pi. It includes
 * definitions for pin configurations and sensor data, as well as function declarations
 * for initializing pins, reading sensor data, and controlling outputs.
 * 
 * @note This file should be used in conjunction with the corresponding implementation
 *       file (`sensor_control.c`) which provides the actual function definitions.
 * 
 */

#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include <wiringPi.h>  /**< Include the WiringPi library for GPIO control */

/**
 * @brief Structure to define GPIO pin configurations.
 * 
 * This structure holds the GPIO pin numbers for temperature, pressure, and
 * humidity sensors, as well as the output control pin.
 */
typedef struct {
    int tempPin;    /**< GPIO pin number for temperature sensor */
    int pressPin;   /**< GPIO pin number for pressure sensor */
    int humidPin;   /**< GPIO pin number for humidity sensor */
    int outputPin;  /**< GPIO pin number for output control */
} PinConfig;

/**
 * @brief Structure to hold sensor data readings.
 * 
 * This structure contains the readings from the temperature, pressure, and
 * humidity sensors.
 */
typedef struct {
    int tempReading;  /**< Reading from the temperature sensor */
    int pressReading; /**< Reading from the pressure sensor */
    int humidReading; /**< Reading from the humidity sensor */
} SensorData;

/**
 * @brief Initializes GPIO pins for sensor interfacing.
 * 
 * Configures the GPIO pins as inputs for sensors and an output for control.
 * 
 * @param pins A pointer to a PinConfig structure with pin assignments.
 * @return int Returns 0 if initialization is successful, or -1 if it fails.
 */
int initializePins(PinConfig *pins);

/**
 * @brief Reads data from the connected sensors.
 * 
 * Retrieves sensor readings from the configured GPIO pins and returns them
 * in a SensorData structure.
 * 
 * @param pins A pointer to a PinConfig structure with pin assignments.
 * @return SensorData A structure containing the sensor readings.
 */
SensorData readSensors(PinConfig *pins);

/**
 * @brief Controls the output pin state.
 * 
 * Sets the output pin to HIGH or LOW based on the provided result value.
 * 
 * @param pins A pointer to a PinConfig structure with pin assignments.
 * @param result An integer where non-zero sets the pin HIGH and zero sets it LOW.
 * @return int Returns 0 to indicate successful operation.
 */
int sendOutput(PinConfig *pins, int result);

/**
 * @brief Resets the output pin state.
 * 
 * Ensures the output pin is set to LOW during cleanup or shutdown.
 * 
 * @param pins A pointer to a PinConfig structure with pin assignments.
 */
void cleanupPins(PinConfig *pins);

#endif /* SENSOR_INTERFACE_H */
