#include "valve.h"
#include <Adafruit_MotorShield.h>


void Valve::open() {
    valveState = true;
};

void Valve::close() {
    valveState = false;
};

bool Valve::state() {
    return valveState;
}