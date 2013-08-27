#include "Arduino.h"
//#include "I2C.h"
#include "MPU6050.h"


void MPU6050::initialize()
{
    I2c = I2C(); // Construct the I2C object
    I2c.i2cInitialize(); // Initialize the Wire object
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
    /******************************* Initialize Buffer **********************************/
    while(I2c.i2cRead(0x3B,I2c.i2cData,6));
    a_x = ((I2c.i2cData[0] << 8) | I2c.i2cData[1]);
    a_y = ((I2c.i2cData[2] << 8) | I2c.i2cData[3]);
    a_z = ((I2c.i2cData[4] << 8) | I2c.i2cData[5]);
    temp = ((I2c.i2cData[6] << 8) | I2c.i2cData[7]);  
    g_x = ((I2c.i2cData[8] << 8) | I2c.i2cData[9]);
    g_y = ((I2c.i2cData[10] << 8) | I2c.i2cData[11]);
    g_z = ((I2c.i2cData[12] << 8) | I2c.i2cData[13]);
    accYangle = (atan2(a_x,a_z)+PI)*RAD_TO_DEG;
    accXangle = (atan2(a_y,a_z)+PI)*RAD_TO_DEG;
    accZangle = (atan2(a_x,a_y)+PI)+RAD_TO_DEG;
    gyroXangle = accXangle;
    gyroYangle = accYangle;
    gyroZangle = accZangle;
    gyroXrate = double(g_x)/131.0;
    gyroYrate = -((double)g_y/131.0);
    gyroZrate = double(g_z)/131.0;
    //kalmanX = Kalman(0);
    //kalmanY = Kalman(0);
    kalmanX.setAngle(accXangle);
    kalmanY.setAngle(accYangle);
    kalmanZ.setAngle(accZangle);
    timer = micros();
}

void MPU6050::readData()
{
    
    while(I2c.i2cRead(0x3B,I2c.i2cData,6));
    a_x = ((I2c.i2cData[0] << 8) | I2c.i2cData[1]);
    a_y = ((I2c.i2cData[2] << 8) | I2c.i2cData[3]);
    a_z = ((I2c.i2cData[4] << 8) | I2c.i2cData[5]);
    temp = ((I2c.i2cData[6] << 8) | I2c.i2cData[7]);  
    g_x = ((I2c.i2cData[8] << 8) | I2c.i2cData[9]);
    g_y = ((I2c.i2cData[10] << 8) | I2c.i2cData[11]);
    g_z = ((I2c.i2cData[12] << 8) | I2c.i2cData[13]);
    accYangle = (atan2(a_x,a_z)+PI)*RAD_TO_DEG;
    accXangle = (atan2(a_y,a_z)+PI)*RAD_TO_DEG;
    accZangle = (atan2(a_x,a_y)+PI)+RAD_TO_DEG;
    gyroXrate = double(g_x)/131.0;
    gyroYrate = -(double)(g_y/131.0);
    gyroZrate = double(g_z/131.0);
    uint32_t timer2 = micros();
    //Serial.print("timer1: ");
    //Serial.println(timer);
    interval = (double(timer2 - timer)/1000000); // normally 0.004s means 250Hz
    //Serial.println(timer2-timer);
    timer = timer2;
    //Serial.print("timer2: ");
    //Serial.println(timer2);
    //Serial.print("interval: ");
    //Serial.println(interval);
    gyroXangle += gyroXrate * interval;
    gyroYangle += gyroYrate * interval;
    gyroZangle += gyroZrate * interval;
    kalAngleX = kalmanX.getAngle(accXangle, gyroXrate, interval);
    kalAngleY = kalmanY.getAngle(accYangle, gyroYrate, interval);
    kalAngleZ = kalmanZ.getAngle(accZangle, gyroZrate, interval);
}

void MPU6050::getRawData()
{
    Serial.print(a_x);Serial.print("\t");
    Serial.print(a_y);Serial.print("\t");
    Serial.print(a_z);Serial.print("\t");
    Serial.print(g_x);Serial.print("\t");
    Serial.print(g_y);Serial.print("\t");
    Serial.print(g_z);Serial.print("\t");  
    Serial.print("\r\n");
}

void MPU6050::getFilteredData()
{
    Serial.print(kalAngleX);Serial.print("\t");
    Serial.print(kalAngleY);Serial.print("\t");
    //Serial.print(kalAngleZ);Serial.print("\t");
    Serial.print("\r\n");
}

double MPU6050::getXangle()
{
  return kalAngleX;
}

double MPU6050::getYangle()
{
  return kalAngleY;
}

void MPU6050::calibration(int sampleNumber)
{
    uint16_t a_xSum = 0;
    uint16_t g_xSum = 0;
    uint16_t a_ySum = 0;
    uint16_t g_ySum = 0; 
    uint16_t a_zSum = 0;
    uint16_t g_zSum = 0; 
    for(int i = 0; i < sampleNumber; i++)
    {
        getRawData();
        
    }
}


