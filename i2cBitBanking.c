
#include "i2cBitbang.h"

void I2CInit()
{
	SDA = 1;
	SCL = 1;
}
 
void I2CStart()
{
	SDA = 0;
	SCL = 0;
}
 
void I2CRestart()
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}
 
void I2CStop()
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	SDA = 1;
}
 
void I2CAck()
{
	SDA = 0;
	SCL = 1;
	SCL = 0;
	SDA = 1;
}
 
void I2CNak()
{
	SDA = 1;
	SCL = 1;
	SCL = 0;
	SDA = 1;
}
 
unsigned char I2CSend(unsigned char Data)
{
	 unsigned char i, ack_bit;
	 for (i = 0; i < 8; i++) {
		if ((Data & 0x80) == 0)
			SDA = 0;
		else
			SDA = 1;
		SCL = 1;
	 	SCL = 0;
		Data<<=1;
	 }
	 SDA = 1;
	 SCL = 1;
	 ack_bit = SDA;
	 SCL = 0;
	 return ack_bit;
}


unsigned char I2CRead()
{
	unsigned char i, Data=0;
	for (i = 0; i < 8; i++) {
		SCL = 1;
		if(SDA)
			Data |=1;
		if(i<7)
			Data<<=1;
		SCL = 0;
	}
	return Data;
}

char readbyte(char ID, char addr)
{
	char s=0;
	I2CInit();
	I2CStart();
	I2CSend(ID);
	I2CSend(addr);
  I2CRestart();
	I2CSend(ID|0x01);
	s=I2CRead();
	
	I2CNak();
	I2CStop();
	return s;
}
void writebyte(char ID, char addr,char *dataByte,int NumOfByte)
{
	char i=0;
	I2CInit();
	I2CStart();
	I2CSend(ID);
	I2CSend(addr);
	for(i=0;i<NumOfByte;i++)
	{
		I2CSend(*dataByte);	
		//I2CAck();
		dataByte++;
	}
	I2CStop();
}