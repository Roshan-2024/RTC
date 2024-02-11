#ifndef DS1307
#define DS1307
#include "i2cBitbang.h"

#define IC_ID 0xD0

#define SECONDS	0x00
#define	MINUTES	0x01
#define HOURS		0x02
#define	DAY			0x03
#define DATE		0x04
#define MONTH		0x05
#define YEAR		0x06
#define CONTROL	0x07

typedef struct 
{
	char sec;
	char min;
	char hr;
	char PM_AM;
	char H12_H24;
	char day;
	char date;
	char month;
	char year;
	
}time;

typedef enum
{
	Hr24,
	Hr12,
}HrFormat;

char getSec();
char getMin();
char getHr();
char getDayOfWeek();
char getDate();
char getMonth();
char getYear();
char getControlReg();

void SetSec(char Sec);
void SetMin(char Min);
void SetHr(char Hr,HrFormat Format);
void SetDayOfWeek(char Weekday);
void SetDate(char date);
void SetMonth(char month);
void SetYear(char year);
void SetControlReg(char val);

void SetDataInRAM(char val,char addr);
char getDataInRAM(char addr);
#endif