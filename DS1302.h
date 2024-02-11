#ifndef DS1302
#define DS1302
#include <reg51.h>

sbit DIO 		= P0^2;
sbit CLK 		= P0^1;
sbit RESET 	= P0^0;


#define ADD_SEC			0x81
#define ADD_MIN			0x83
#define ADD_HR			0x85
#define ADD_DATE		0x87
#define ADD_MONTH		0x89
#define ADD_DAY			0x8B
#define ADD_YEAR		0x8D

void enableIC();
void DisableIC();
void SPI_Init();
void SPI_BytesWrite(char Data,int NumOfBytes);
char SPI_BitRead();

#endif