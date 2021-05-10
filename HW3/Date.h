#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 2020

typedef struct
{
	int			day;
	int			month;
	int			year;
	char*		fullDate;
}Date;

void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
void	printDate(const Date* pDate);
void readDateFromBinFile(FILE *file, Date* date);
void writeDateToBinFile(FILE *file, Date *date);
#endif
