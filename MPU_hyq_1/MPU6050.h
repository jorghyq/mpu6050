#ifndef _MPU6050_H
#define _MPU6050_H

#include "Arduino.h"
#include "I2C.h"
#include "inttypes.h"
#include "Kalman.h"

//const uint8_t IMUAddress = 0x68; // AD0 is logic low on the PCB
//const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication
#define CALIBRATION_SAMPLES 50
#define ACC_RATE 0.001
#define GYRO_RATE 0.001
class MPU6050
{
    public:
        
        MPU6050() {};
        void initialize(); // Initialization
        void readData();
        void getRawData();
        void calibration(int sampleNumber);
        void getFilteredData();
        double getXangle();
        double getYangle();
        I2C I2c;
    private:
        int16_t a_x, a_y, a_z;
        int16_t g_x, g_y, g_z;
        int16_t temp;
        double accXangle, accYangle, accZangle;
        double gyroXrate, gyroYrate, gyroZrate;
        double gyroXangle, gyroYangle, gyroZangle;
        int16_t a_xBias, a_yBias, a_zBias;
        int16_t g_xBias, g_yBias, g_zBias;
        uint32_t timer; // Used to calculate rotated angle with gyro output
        double interval;
        Kalman kalmanX;
        Kalman kalmanY;
        Kalman kalmanZ;
        double kalAngleX, kalAngleY, kalAngleZ;
};
#endif
