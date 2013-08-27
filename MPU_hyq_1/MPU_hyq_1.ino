#include <Wire.h>
#include <Servo.h>
#include "MPU6050.h" // Source: https://github.com/TKJElectronics/KalmanFilter

//I2C i2c;
MPU6050 myMPU;
Servo servoX;
int pos = 0;
double angleX = 0;
double angleY = 0;
int setPos = 0;
int a=0;
/* IMU Data */
double p; // p constant for PID
double i; // i constant for PID
double d; // d constant for PID
void setup() {  
  Serial.begin(115200);
  servoX.attach(9);
  myMPU.initialize();
  delay(1000); // Wait for sensor to stabilize
  
  /* Set kalman and gyro starting angle */
   //myMPU.getData();
  while(fabs(angleX-180)>5)
  {
     servoX.write(pos);
     myMPU.readData();
     angleX = myMPU.getXangle();
     Serial.print("MPU angle: ");
     Serial.println(angleX); 
     //setPos = pos;
     Serial.print("Servo position: ");
     Serial.println(pos);
     delay(15);
     pos = pos + 1;
       
  }
  setPos = pos;
  Serial.print("set position: ");
  Serial.println(setPos);
  servoX.write(setPos);
  //timer = micros();
}

void loop() {
  /* Update all the values */
  a = 20;  
  myMPU.readData();
  angleX = myMPU.getXangle();
  if(angleX > 180)
  {
    servoX.write(setPos+a);
    //a = a + 5;
  }
  //a = 5;
  else
  {
    servoX.write(setPos-a);
    //a = a + 5;
  }
  
  /* Print Data */
  //myMPU.getFilteredData();
  delay(1);
}
