#ifndef _MPU6050_H
#define _MPU6050_H

#include "Arduino.h"
#include "I2C.h"
#include "inttypes.h"
//const uint8_t IMUAddress = 0x68; // AD0 is logic low on the PCB
//const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication
//typedef 
class MPU6050
{
    public:
        
        MPU6050() {};
        void initialize();
        void getData();
        void outputData();
        void calibration();
        I2C I2c;
    private:
        int16_t a_x, a_y, a_z;
        int16_t g_x, g_y, g_z;
        int16_t temp;
        double accYangle, accXangle, accZangle;
        int16_t a_xBias, a_yBias, a_zBias;
        int16_t g_xBias, g_yBias, g_zBias;
};
#endif
