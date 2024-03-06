#include "moisture_sensor.h"

// From the Adafruit documentation were 200 is very dry and 2000 is very wet.
// https://www.adafruit.com/product/4026#technical-details
#define DEFAULT_LOWER_CAPATIENCE 200
#define DEFAULT_UPPER_CAPATIENCE 2000

MoistureSensor::MoistureSensor(Adafruit_seesaw& seesaw) : ss(seesaw) {
  this->lowerCapatience = DEFAULT_LOWER_CAPATIENCE;
  this->upperCapatience = DEFAULT_UPPER_CAPATIENCE;
}

float MoistureSensor::GetTemperature() {
  return this->ss.getTemp();
}

double MoistureSensor::GetMoisture() {
  uint16_t capatience = this->ss.touchRead(0);

  // bind the capatience in the calibrated ranges.
  capatience =
      constrain(capatience, this->lowerCapatience, this->upperCapatience);

  return ((double)(capatience - this->lowerCapatience) / (this->upperCapatience - this->lowerCapatience));
}
