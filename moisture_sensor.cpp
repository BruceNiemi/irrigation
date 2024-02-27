#include "moisture_sensor.h"

// From the Adafruit documentation were 200 is very dry and 2000 is very wet.
// https://www.adafruit.com/product/4026#technical-details
#define DEFAULT_LOWER_CAPATIENCE 200
#define DEFAULT_UPPER_CAPATIENCE 2000
// Reading the documentation this is the default I2C address for the sensor
// https://cdn-learn.adafruit.com/downloads/pdf/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor.pdf
#define I2C_ADDRESS 0x36

MoistureSensor::MoistureSensor(Adafruit_seesaw seesaw) : ss(seesaw){
  this->lowerCapatience = DEFAULT_LOWER_CAPATIENCE;
  this->upperCapatience = DEFAULT_UPPER_CAPATIENCE;
}

float MoistureSensor::GetTemperature()
{
  return this->ss.getTemp();
}

double MoistureSensor::GetMoisture()
{
  uint16_t capatience = this->ss.touchRead(0);

  // bind the capatience in the calibrated ranges.
  capatience = constrain(capatience, this->lowerCapatience, this->upperCapatience);

  double moisturePercentage = ((double)(capatience - this->lowerCapatience) / (this->upperCapatience - this->lowerCapatience)) * 100.0;
  
  return constrain(moisturePercentage, 0.0, 100.0);
}

bool MoistureSensor::IsConnected() 
{
  // This is the status code from the sample code provided by adafruit.
  return this->ss.begin(I2C_ADDRESS);
}