#ifndef _Mpu6050_h
#define _Mpu6050_h

// Define the Mpu6050 object, which can set up mpu6050 and output the raw data 
// after calibration
//typedef signed int int16_t
#define SAMPLES 5
#define CALIBRATION_SAMPLES 128
class Mpu6050
{
    public:
        void initialize();
        void calibration();
        int16_t getTemp ();
        Mpu6050()
        {
            
            };
    private:
        int16_t a_x;
        int16_t a_y;
        int16_t a_z;
        int16_t g_x;
        int16_t g_y;
        int16_t g_z;
        int16_t temp;
        uint8_t i2cData[14]; // buffer for i2c
    }

const uint8_t IMUAddress = 0x68; // AD0 is logic low on the PCB
const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication

uint8_t i2cWrite(uint8_t registerAddress, uint8_t data, bool sendStop) {
  return i2cWrite(registerAddress,&data,1,sendStop); // Returns 0 on success
}

uint8_t i2cWrite(uint8_t registerAddress, uint8_t* data, uint8_t length, bool sendStop) {
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  Wire.write(data, length);
  return Wire.endTransmission(sendStop); // Returns 0 on success
}

uint8_t i2cRead(uint8_t registerAddress, uint8_t* data, uint8_t nbytes) {
  uint32_t timeOutTimer;
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  if(Wire.endTransmission(false)) // Don't release the bus
    return 1; // Error in communication
  Wire.requestFrom(IMUAddress, nbytes,(uint8_t)true); // Send a repeated start and then release the bus after reading
  for(uint8_t i = 0; i < nbytes; i++) {
    if(Wire.available())
      data[i] = Wire.read();
    else {
      timeOutTimer = micros();
      while(((micros() - timeOutTimer) < I2C_TIMEOUT) && !Wire.available());
      if(Wire.available())
        data[i] = Wire.read();
      else
        return 2; // Error in communication
    }
  }
  return 0; // Success
}
