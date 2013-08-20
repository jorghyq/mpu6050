#ifndef _I2C_H_
#define _I2C_H

#include "Arduino.h"
#include "inttypes.h"
const uint8_t IMUAddress = 0x68; // AD0 is logic low on the PCB
const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication
//typedef 
class I2C
{
    public:
        I2C() {};
        void i2cInitialize();
        uint8_t i2cWrite(uint8_t registerAdress, uint8_t data, bool sendStop);
        uint8_t i2cWrite(uint8_t registerAddress, uint8_t* data, uint8_t length, bool sendStop);
	uint8_t i2cRead(uint8_t registerAddress, uint8_t* data, uint8_t nbytes);
        uint8_t i2cData[14]; // buffer for i2c
    private:
        
};
#endif
