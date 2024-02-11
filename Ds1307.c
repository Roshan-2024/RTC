#include"DS1307.h"
char getSec()
{
	return readbyte(IC_ID,SECONDS );
}

void SetSec(char Sec){
	writebyte(IC_ID,SECONDS,&Sec,1);
}

char getMin()
{
	return readbyte(IC_ID,MINUTES );
}
void SetMin(char Min){
	writebyte(IC_ID,SECONDS,&Min,1);
}

char getHr()
{
	//char a;
//	a = readbyte(IC_ID, HOURS);
//	if(a&0x80)
//	{
//		return readbyte(IC_ID, HOURS)&0x3F;
//	}
//	else
//	{
//		return readbyte(IC_ID, HOURS)&0x0F;
//	}	
	return readbyte(IC_ID, HOURS);
}

void SetHr(char Hr,HrFormat Format){
	
	if(Format == Hr12)
	{
		Hr = Hr | 0x80;
	}
	else
	{
		;
	}
	writebyte(IC_ID,SECONDS,&Hr,1);
}
char getDate()
{
	return readbyte(IC_ID,DATE);
}


void SetDate(char date)
{
	
	writebyte(IC_ID,SECONDS,&date,1);
}
char getDayOfWeek()
{
	return readbyte(IC_ID,DAY);
}

void SetDayOfWeek(char Weekday)
{
	writebyte(IC_ID,SECONDS,&Weekday,1);
}
char getMonth()
{
	return readbyte(IC_ID,MONTH);
}

void SetMonth(char month)
{
	writebyte(IC_ID,SECONDS,&month,1);
}
char getYear()
{
	return readbyte(IC_ID,YEAR);
}

void SetYear(char year)
{
	writebyte(IC_ID,SECONDS,&year,1);
}

char getControlReg()
{
	return readbyte(IC_ID,CONTROL);
}


void SetControlReg(char val)
{
	writebyte(IC_ID,SECONDS,&val,1);
}


void SetDataInRAM(char val,char addr){
	writebyte(IC_ID,addr,&val,1);
}
char getDataInRAM(char addr){
	return readbyte(IC_ID,addr);
}