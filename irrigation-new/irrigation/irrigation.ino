#include <ArduinoJson.h>
#include "Adafruit_seesaw.h"
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>


Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {
  myStepper1->onestep(FORWARD, SINGLE);
}
void backwardstep1() {
  myStepper1->onestep(BACKWARD, SINGLE);
}

// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);


Adafruit_seesaw ss;

void setup() {
  Serial.begin(115200);

  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }

  AFMStop.begin(); // Start the top shield
  stepper1.setMaxSpeed(50);
  stepper1.setAcceleration(200);
  stepper1.setCurrentPosition(0);  
}

bool open = false;
unsigned long lastMillis = 0;

void loop() {
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  if(capread < 400 && !open) {
    
    // Move the stepper motor by 45 degrees in one direction
    stepper1.moveTo(35);
    
    // Wait for the motor to reach its target position
    while (stepper1.distanceToGo() != 0) {
      stepper1.run();
    }
    open = true;
  } else if (capread >= 400 && open) {
    // Move the stepper motor by 45 degrees in the opposite direction
    stepper1.moveTo(-35);
    
    // Wait for the motor to reach its target position
    while (stepper1.distanceToGo() != 0) {
      stepper1.run();
    }
    open = false;
  }
  
  if(millis() > lastMillis + 5000) {
    StaticJsonDocument<200> document;

    document["open"] = open;
    document["moisture"] = getMoisture();
    document["temp"] = tempC;

    String jsonString;
    serializeJson(document, jsonString);
    Serial.println(jsonString);
    lastMillis = millis();
   }

  // Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  // Serial.print("Capacitive: "); Serial.println(capread);
  // Serial.print("Ratio: "); Serial.println(getMoisture());
  delay(100);
}

double getMoisture() {
  uint16_t capatience = ss.touchRead(0);

  // bind the capatience in the calibrated ranges.
  capatience = constrain(capatience, 300, 950);

  return (double)(capatience - 300) / (950 - 300);
}


