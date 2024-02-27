#ifndef MOISTURE_SENSOR_H_
#define MOISTURE_SENSOR_H_

#include <Arduino.h>

class MoistureSensor {
    /**
     * Get the temperature in degrees Celsius.
     * 
     * This function retrieves the current temperature from the moisutre sensor.
     * 
     * @return the temperature in degrees Celsius, or an error value if the sensor
     *         is unable to providee a reading ()
    */  
    virtual float GetTemperature() = 0;

    /**
      * Get the moisture level as percentage.
      * 
      * This function retrieves the current mositure level from the moisture sensor.
      * 
      * @return The moisutre level as percentage.
      */
    virtual double GetMoisture() = 0;
};

#endif // MOISTURE_SENSOR_H_