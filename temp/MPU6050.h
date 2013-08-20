#ifndef _MPU6050_H
#define _MPU6050_H

#include "Arduino.h"
#include "inttypes.h"
//const uint8_t IMUAddress = 0x68; // AD0 is logic low on the PCB
//const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication
//typedef 
class MPU6050
{
    public:
        MPU6050() {};
        void initialize();
        void calibration();
    private:
        int16_t a_x;
        int16_t a_y;
        int16_t a_z;
        int16_t g_x;
        int16_t g_y;
        int16_t g_z;
        int16_t temp;
        uint8_t i2cData[14]; // buffer for i2c
};
#endif
