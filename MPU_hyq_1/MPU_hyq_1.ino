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

void setup() {  
  Serial.begin(115200);
  myMPU.initialize();
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
