#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"
#include "Date.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		puts("Enter Flight Date dd/mm/yyyy\t");
		myGets(date, MAX_STR_LEN);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}

void readDateFromBinFile(FILE *file, Date* date)
{
	fread(&date->day, sizeof(int), 1, file);
	fread(&date->month, sizeof(int), 1, file);
	fread(&date->year, sizeof(int), 1, file);
	int fullDateLen = 0;
	fread(&fullDateLen, sizeof(int), 1, file);
	date->fullDate = (char*)malloc(sizeof(char)*fullDateLen);
	fread(date->fullDate, sizeof(char), 11, file);
}
void writeDateToBinFile(FILE *file, Date *date)
{
	fwrite(&date->day, sizeof(int), 1, file);
	fwrite(&date->month, sizeof(int), 1, file);
	fwrite(&date->year, sizeof(int), 1, file);
	int fullDateLen = 11;
	fwrite(&fullDateLen, sizeof(int), 1, file);
	fwrite(date->fullDate, sizeof(char), 11, file);
}

int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	char* theFullDate="";
	theFullDate = (char*)malloc(strlen(date) * sizeof(char));
	if (strlen(date) != 10)
		return 0;
	if ( (date[2] != '/') || (date[5] != '/'))
		return 0;
	sscanf(date, "%d/%d/%d", &day, &month, &year);
	strcpy(theFullDate,date);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;
	pDate->fullDate = theFullDate;
	return 1;
}

void printDate(const Date* pDate)
{
	printf("Date: %d/%d/%d\n", pDate->day, pDate->month, pDate->year);
}
