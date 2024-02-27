#ifndef MOISTURE_SENSOR_H_
#define MOISTURE_SENSOR_H_

#include <Arduino.h>

class MoistureSensor {
    /**
     * Get the temperature in degrees Celsius.
     * 
     * This function retrieves the current temperature from the moisutre sensor.
     * 
     * @return the temperature in degrees Celsius.
     */  
    float GetTemperature();

    /**
      * Get the moisture level as percentage.
      * 
      * This function retrieves the current mositure level from the moisture sensor.
      * 
      * @return The moisutre level as percentage.
      */
    double GetMoisture();

    /**
     * Checks if the moisture sensor is connected.
     * 
     * @return true if the sensor is connected, false otherwise.
     */
    bool IsConnected();
};

#endif // MOISTURE_SENSOR_H_