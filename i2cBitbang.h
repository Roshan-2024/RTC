#ifndef I2C_BANG
#define I2C_BANG
#include "i2cWrapper.h"


unsigned char I2CSend(unsigned char Data);
unsigned char I2CRead();
char readbyte(char ID,char addr);
void  writebyte(char ID, char addr,char *dataByte,int NumOfByte);
	
#endif