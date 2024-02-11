#include "DS1302.h"
#define BCD_TO_DEC(val)             ((val / 16 * 10) + (val % 16))
void SPI_Init()
{
	DIO		= 1;
	CLK		= 0;
	RESET =	0;
}
void enableIC()
{
		RESET=1;
}
void DisableIC()
{
		RESET=0;
}
void SPI_BytesWrite(char Data,int NumOfBytes)
{
	int i=0,j=0;

//	for(i=0;i<NumOfBytes;i++)
//	{s
		for(j=0;j<8;j++)
			{
				if((Data&0x01) == 1)
				{
					DIO = 1;
				}
				else
				{
					DIO = 0;
				}
				Data=Data >> 1;
				CLK =1;
				CLK =0;
			}
//	}

	
}
char SPI_BitRead()
{
	char Data=0x00;
	int j=0;
	for(j=0;j<8;j++)
			{
				
				if(DIO == 1)
				{
					Data = Data | (0x01<<j);
				}
				else
				{
					
				}
				CLK =1;
				CLK =0;
				
			}
			Data =BCD_TO_DEC(Data) ;
			return Data;
}