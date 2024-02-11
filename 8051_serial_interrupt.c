
#include <reg51.h>			/* Include x51 header file */
sfr lcd_data_port=0x90;				 				/* P1 port as data port */
sbit rs=P2^0;        					 				/* Register select pin */
sbit rw=P2^1;        									/* Read/Write pin */
sbit en=P2^2;        									/* Enable pin */
volatile CHAR=0x00;
void LCD_Char (unsigned char char_data);
void Ext_int_Init()				
{
	EA  = 1;							/* Enable global interrupt */
	ES = 1;      					/* Enable Ext. interrupt0 */			
}

void UART_Init()
{
	TMOD = 0x20;					/* Timer 1, 8-bit auto reload mode */
	TH1 = 0xFD;						/* Load value for 9600 baud rate */
	SCON = 0x50;					/* Mode 1, reception enable */
	TR1 = 1;							/* Start timer 1 */
}

void Serial_ISR() interrupt 4    
{
	if(RI)	
	{
		CHAR = SBUF;						
		LCD_Char(CHAR);
		RI = 0;								/* Clear RI flag */
	}
	if(TI)
	{
		TI=0;
	}
} 
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
	//P1 = 0x00;						/* Make P1 output */
	Ext_int_Init();  			/* Call Ext. interrupt initialize */
	UART_Init();
	LCD_Init();	
	//String("test");
	LCD_String_xy(0,0," PRESS 1 TO CLR");
	LCD_Command (0xC0);								/* cursor at home position */
	while(1)
	{
		if(CHAR =='1')
		{
			CHAR =0x00;
			LCD_Command (0x01);
			LCD_String_xy(0,0,"PRESS 1 TO CLR");
			LCD_Command (0xC0);
		}
		
	}
}
