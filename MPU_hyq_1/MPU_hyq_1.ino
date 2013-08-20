#include <Wire.h>
#include "MPU6050.h" // Source: https://github.com/TKJElectronics/KalmanFilter

//I2C i2c;
MPU6050 myMPU;
/* IMU Data */
int16_t accX, accY, accZ;
int16_t tempRaw;
int16_t gyroX, gyroY, gyroZ;

double accXangle, accYangle, accZangle; // Angle calculate using the accelerometer
double temp; // Temperature
double gyroXangle, gyroYangle, gyroZangle; // Angle calculate using the gyro
double compAngleX, compAngleY; // Calculate the angle using a complementary filter
double kalAngleX, kalAngleY, kalAngleZ; // Calculate the angle using a Kalman filter

uint32_t timer;
//uint8_t I2c.i2cData[14]; // Buffer for I2C data

void setup() {  
  Serial.begin(115200);
  //I2c.i2cInitialize();
  myMPU.initialize();
  //Wire.begin();
//  I2c.i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
//  I2c.i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
//  I2c.i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
//  I2c.i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
//  while(I2c.i2cWrite(0x19,I2c.i2cData,4,false)); // Write to all four registers at once
//  while(I2c.i2cWrite(0x6B,0x01,true)); // PLL with X axis gyroscope reference and disable sleep mode 
//  
//  while(I2c.i2cRead(0x75,I2c.i2cData,1));
//  if(I2c.i2cData[0] != 0x68) { // Read "WHO_AM_I" register
//    Serial.print(F("Error reading sensor"));
//    while(1);
//  }
  
  delay(100); // Wait for sensor to stabilize
  
  /* Set kalman and gyro starting angle */
   myMPU.getData();
  
  timer = micros();
}

void loop() {
  /* Update all the values */  
  myMPU.getData();
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // We then convert it to 0 to 2π and then from radians to degrees
   
  timer = micros();
  
  temp = ((double)tempRaw + 12412.0) / 340.0;
  
  /* Print Data */
  myMPU.outputData();
  delay(1);
}
