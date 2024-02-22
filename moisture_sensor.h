#ifndef MOISTURE_SENSOR_H_
#define MOISTURE_SENSOR_H_

#include "Adafruit_seesaw.h"
#include <Arduino.h>

class MoistureSensor {
  private:
    Adafruit_seesaw ss;
    uint16_t lowerCapatience;
    uint16_t upperCapatience;

  public:
    MoistureSensor(Adafruit_seesaw ss);

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
};

#endif