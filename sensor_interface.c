/**
 * @file sensor_control.c
 * @brief Provides functionality to interface with various sensors and control outputs.
 * 
 * This file contains functions for initializing GPIO pins, reading sensor data,
 * and controlling output pins using the WiringPi library. The functionality is
 * designed to work with sensors connected to specific GPIO pins on a Raspberry Pi.
 * 
 * Functions included:
 * - `initializePins`: Sets up GPIO pins as inputs or outputs.
 * - `readSensors`: Reads digital values from sensor pins and stores them in a `SensorData` structure.
 * - `sendOutput`: Controls the state of an output pin based on a given result.
 * - `cleanupPins`: Resets the output pin to a low state during cleanup.
 * 
 * This file depends on the WiringPi library for GPIO control and requires the 
 * `sensor_interface.h` header file for definitions related to pin configurations
 * and sensor data structures.
 * 
 * @note Ensure that the WiringPi library is properly installed and configured
 *       on the system where this code is executed.
 */

#include <stdio.h>  // Standard I/O operations for input and output functions
#include <wiringPi.h>  // WiringPi library for GPIO control and digital I/O
#include "sensor_interface.h"  // Header file defining PinConfig and SensorData structures

/**
 * @brief Initializes the GPIO pins used for sensor inputs and output.
 * 
 * This function sets up the WiringPi library and configures the specified
 * GPIO pins as either input or output according to their intended use.
 * 
 * @param pins A pointer to a PinConfig structure containing pin assignments.
 * @return int Returns 0 if initialization is successful; otherwise, returns -1.
 */
int initializePins(PinConfig *pins) {
    // Initialize the WiringPi library
    if (wiringPiSetup() == -1) {
        // Return -1 if the setup fails
        return -1;
    }
    
    // Set pin modes based on their roles
    pinMode(pins->tempPin, INPUT);
    pinMode(pins->pressPin, INPUT);
    pinMode(pins->humidPin, INPUT);
    pinMode(pins->outputPin, OUTPUT);
    
    // Return 0 indicating successful pin setup
    return 0;
}

/**
 * @brief Reads the current values from the sensor pins.
 * 
 * This function retrieves the digital readings from the sensor pins and
 * stores them in a SensorData structure.
 * 
 * @param pins A pointer to a PinConfig structure containing pin assignments.
 * @return SensorData A structure containing the sensor readings.
 */
SensorData readSensors(PinConfig *pins) {
    // Create a SensorData structure to hold the sensor readings
    SensorData data = {0, 0, 0};
    
    // Read values from sensor pins
    data.tempReading = digitalRead(pins->tempPin);
    data.pressReading = digitalRead(pins->pressPin);
    data.humidReading = digitalRead(pins->humidPin);
    
    // Return the collected sensor data
    return data;
}

/**
 * @brief Sets the state of the output pin based on the result value.
 * 
 * This function controls the output pin, setting it to HIGH or LOW
 * based on the provided result value.
 * 
 * @param pins A pointer to a PinConfig structure containing pin assignments.
 * @param result An integer value where non-zero sets the pin HIGH, and zero sets it LOW.
 * @return int Returns 0 to indicate that the output operation was performed successfully.
 */
int sendOutput(PinConfig *pins, int result) {
    // Set the output pin to HIGH or LOW based on the result value
    digitalWrite(pins->outputPin, result ? HIGH : LOW);
    
    // Return 0 to indicate successful output operation
    return 0;
}

/**
 * @brief Resets the state of the output pin.
 * 
 * This function sets the output pin to LOW to deactivate it. This is
 * typically called during cleanup or shutdown processes to ensure
 * the pin is not left in an active state.
 * 
 * @param pins A pointer to a PinConfig structure containing pin assignments.
 */
void cleanupPins(PinConfig *pins) {
    // Ensure the output pin is set to LOW during cleanup
    digitalWrite(pins->outputPin, LOW);
}
