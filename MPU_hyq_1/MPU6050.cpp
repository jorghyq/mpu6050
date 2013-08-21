#include "Arduino.h"
//#include "I2C.h"
#include "MPU6050.h"


void MPU6050::initialize()
{
    I2c = I2C();
    I2c.i2cInitialize();
    I2c.i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
    I2c.i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
    I2c.i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
    I2c.i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
    while(I2c.i2cWrite(0x19,I2c.i2cData,4,false)); // Write to all four registers at once
    while(I2c.i2cWrite(0x6B,0x01,true)); // PLL with X axis gyroscope reference and disable sleep mode 
  
    while(I2c.i2cRead(0x75,I2c.i2cData,1));
    if(I2c.i2cData[0] != 0x68) { // Read "WHO_AM_I" register
      Serial.print(F("Error reading sensor"));
      while(1);
    }
}

void MPU6050::getData()
{
    while(I2c.i2cRead(0x3B,I2c.i2cData,6));
    a_x = ((I2c.i2cData[0] << 8) | I2c.i2cData[1]);
    a_y = ((I2c.i2cData[2] << 8) | I2c.i2cData[3]);
    a_z = ((I2c.i2cData[4] << 8) | I2c.i2cData[5]);
    tempRaw = ((I2c.i2cData[6] << 8) | I2c.i2cData[7]);  
    g_x = ((I2c.i2cData[8] << 8) | I2c.i2cData[9]);
    g_y = ((I2c.i2cData[10] << 8) | I2c.i2cData[11]);
    g_z = ((I2c.i2cData[12] << 8) | I2c.i2cData[13]);
    accYangle = (atan2(a_x,a_z)+PI)*RAD_TO_DEG;
    accXangle = (atan2(a_y,a_z)+PI)*RAD_TO_DEG;
    accZangle = (atan2(a_x,a_y)+PI)+RAD_TO_DEG;
}

void MPU6050::outputData()
{
    Serial.print(accXangle);Serial.print("\t");
    Serial.print(accYangle);Serial.print("\t");  
    Serial.print("\r\n");
}

void MPU6050::calibration(int sampleNumber)
{
    uint16_t a_xSum = 0;
    uint16_t g_xSum = 0; 
    for(int i = 0; i < sampleNumber; i++)
    {
        getdata();
        a_
    }
}


