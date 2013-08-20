#include "Arduino.h"
#include "Wire.h"
#include "MPU6050.h"


void MPU6050::initialize()
{
    double a = 10;
    delay(100);
    Serial.println("hello");
    Wire.begin();
    Wire.beginTransmission(0x52);
}
