
#include <reg51.h>			/* Include x51 header file */
#include "DS1302.h"
#include <stdio.h>
#include <string.h>
sfr lcd_data_port=0x90;				 				/* P1 port as data port */
sbit rs=P2^0;        					 				/* Register select pin */
sbit rw=P2^1;        									/* Read/Write pin */
sbit en=P2^2;        									/* Enable pin */


sbit LED = P3^5;
int i=0;
sbit BUZER =P3^5;
int counter =0;
int commaCounter=0;
volatile char CHAR=0x00;
char GPSdata[50];

typedef struct {
		char sec,min,hr,day,date,month,year;
	}time;
time T;
char FirstRow[16];
char SecondRow[16];	
void LCD_Char (unsigned char char_data);


void Ext_int_Init()				
{
	EA  = 1;							/* Enable global interrupt */
	ES 	= 1;      					/* Enable Ext. interrupt0 */			
}

void UART_Init()
{
	TMOD = 0x20;					/* Timer 1, 8-bit auto reload mode */
	TH1 = 0xFD;						/* Load value for 9600 baud rate */
	SCON = 0x50;					/* Mode 1, reception enable */
	TR1 = 1;							/* Start timer 1 */
}
//$GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68


void Transmit_data(char tx_data)
{
	SBUF = tx_data;				/* Load char in SBUF register */
	while (TI==0);				/* Wait until stop bit transmit */
	TI = 0;								/* Clear TI flag */
}
void String(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)/* Send each char of string till the NULL */
	{
		Transmit_data(str[i]);	/* Call transmit data function */
	}
}
void Serial_ISR() interrupt 4    
{
	if(RI)	
	{
		CHAR = SBUF;
		
		if((counter == 0) && (CHAR == '$'))
		{
			counter ++;
			commaCounter=0;
		}
		else if((counter == 1) && (CHAR == 'G'))
		{
			counter ++;
		}
		
		else if((counter == 2) && (CHAR == 'P'))
		{
			counter ++;
		}
		else if((counter == 3) && (CHAR == 'R'))
		{
			counter ++;
		}
		else if((counter == 4) && (CHAR == 'M'))
		{
			counter ++;
		}
		else if((counter == 5) && (CHAR == 'C'))
		{
			counter ++;
		}
		else if((counter == 6) && (CHAR == ','))
		{
			counter ++;
		}	
		else if(counter >=7)
		{
			if(CHAR == ',')
			{
				commaCounter++;
				if(commaCounter == 10)
				{

					counter =0;		
				}
			}
			GPSdata[counter-7] = CHAR;
			counter++;
			
		}
		
		RI = 0;								/* Clear RI flag */
	}
	else
	{
		counter =0;
	}
	if(TI)
	{
		TI=0;
	}
} 



/* LCD functions*/
void delay(unsigned int count)    		/* Function to provide delay Approx 1ms */
{
    int i,j;
     for(i=0;i<count;i++)
     for(j=0;j<112;j++);
}

void LCD_Command (unsigned char cmd)   /* LCD16x2 command funtion */
{
     lcd_data_port= cmd;
     rs=0;														/* command reg. */
     rw=0;														/* Write operation */
     en=1; 
	 delay(1);
	 en=0;
	 delay(5);
}

void LCD_Char (unsigned char char_data)							/* LCD data write function */
{
    lcd_data_port=char_data;
     
    rs=1;							/*Data reg.*/
    rw=0;						/*Write operation*/
		en=1;   				
	  delay(1);
		en=0;
		delay(5);
}

void LCD_String (unsigned char *str)							/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)							/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);							/* Call LCD data write */
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD function */
{
	if (row == 0)
	LCD_Command((pos & 0x0F)|0x80);					/* Command of first row and required position<16 */
	else if (row == 1)
	LCD_Command((pos & 0x0F)|0xC0);					/* Command of first row and required position<16 */
	LCD_String(str);								/* Call LCD string function */
}

void LCD_Init (void)								/* LCD Initialize function */
{	
	delay(20);									/* LCD Power ON Initialization time >15ms */
	
	LCD_Command (0x38);								/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);								/* Display ON Cursor OFF */
	LCD_Command (0x06);								/* Auto Increment cursor */
	LCD_Command (0x01);								/* clear display */
	LCD_Command (0x80);								/* cursor at home position */
}

void main()
{
	Ext_int_Init();  			/* Call Ext. interrupt initialize */
	UART_Init();
	LCD_Init();	
	//String("test");


	
	while(1)
	{
		
		
		
		if(commaCounter == 10)
		{
			
			Transmit_data('\r');
			Transmit_data('\n');
			//String(GPSdata);
			commaCounter =0;
			for(i=0;i<=100;i++)
			{
				
				Transmit_data(GPSdata[i]);
				if(GPSdata[i] == ',')
				{
					commaCounter++;
					if(commaCounter == 10)
					{
						commaCounter =0;
						break;
					}
					Transmit_data('\r');
					Transmit_data('\n');
				}
			}
			
			
			memset(GPSdata,0,sizeof(GPSdata));
			
		}
		
//		LCD_Command (0x01);	
//		
//		SPI_Init();
//		enableIC();
//		SPI_BytesWrite(ADD_SEC,1);
//		T.sec = SPI_BitRead();
//		DisableIC();
//		
//		if(T.sec>=10 && T.sec <=20)
//		{
//			LED =1;
//		}
//		else
//		{
//			LED =0;
//		}
		
		
		
//		SPI_Init();
//		enableIC();
//		SPI_BytesWrite(ADD_MIN,1);
//		T.min = SPI_BitRead();
//		DisableIC();
//		
//		SPI_Init();
//		enableIC();
//		SPI_BytesWrite(ADD_HR,1);
//		T.hr = SPI_BitRead();
//		DisableIC();
//		
//		sprintf(FirstRow,"%d:%d:%d\r\n",T.hr&0x00FF,T.min&0x00FF,T.sec&0x00FF);
//		LCD_Command (0x80);
//		LCD_String(FirstRow);
//		String(FirstRow);
//		
//		
//		SPI_Init();
//		enableIC();
//		SPI_BytesWrite(ADD_DATE,1);
//		T.date = SPI_BitRead();
//		DisableIC();
//		
//		SPI_Init();
//		enableIC();
//		SPI_BytesWrite(ADD_MONTH,1);
//		T.month = SPI_BitRead();
//		DisableIC();
//		
//		SPI_Init();
//		enableIC();
//		SPI_BytesWrite(ADD_YEAR,1);
//		T.year = SPI_BitRead();
//		DisableIC();
//		
//		sprintf(SecondRow,"%d/%d/%d\r\n",T.date&0x00FF,T.month&0x00FF,T.year&0x00FF);
//		LCD_Command (0xC0);
//		LCD_String(SecondRow);
//		String(SecondRow);
//		
//		delay(200);
		
	}
}
//11010110