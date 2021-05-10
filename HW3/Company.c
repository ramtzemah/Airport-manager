#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"

typedef enum
{
	eNotSort,eHour, eDate,eSourceCode, eDestCode, eNofOptions
} eMenuOptions;

const char* strCompany[eNofOptions] = { "Not sort", "By hour","By date","By source code",
								 "By dest code"};

#define EXIT			-1
int Companymenu();

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->bSearchPosabilty = 0;
	L_init(&pComp->allDates);

}

int	addFlight(Company* pComp,const AirportManager* pManager)
{
	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount+1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1,sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount],pManager);
	pComp->flightCount++;
	pComp->bSearchPosabilty = 0;
	char* date;
	date = pComp->flightArr[pComp->flightCount - 1]->date.fullDate;
	NODE* pnode = (pComp->allDates).head.next;
	int check = 0;
		while(pnode != NULL)
		{
			if (strcmp((char*)pnode->key, date) == 0) {
				check++;
			}
			pnode = pnode->next;
		} 
	if (check==0)
	{
		pnode = L_insert(&pComp->allDates.head, date);
	}
	return 1;
}

void printCompany(const Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight*), printFlight);
	L_print(&pComp->allDates, printDatesChar);
}

void	freeCompany(Company* pComp)
{

	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight*), freeFlight);
	free(pComp->name);
}

void initCompanyFromBinaryFile(FILE* file, Company* pComp)
{
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	L_init(&(pComp->allDates));
	int nameLen, numOfFlights;
	fread(&nameLen, sizeof(int), 1, file);
	pComp->name = (char*)malloc(sizeof(char)*nameLen);
	if (!pComp->name)
	{
		fclose(file);
		return;
	}
	fread(pComp->name, sizeof(char), nameLen, file);
	fread(&numOfFlights, sizeof(int), 1, file);
	for (int i = 0; i < numOfFlights; i++)
	{
		pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
		if (!pComp->flightArr)
		{
			fclose(file);
			return;
		}
		pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
		if (!pComp->flightArr[pComp->flightCount])
		{
			fclose(file);
			return;
		}
		readFlightFromBinFile(file, pComp->flightArr[pComp->flightCount]);
		
		pComp->flightCount++;

	}
	addFlightDateToDateList(pComp);
}
void addFlightDateToDateList(Company* pComp)
{
	for (int i = 0; i < pComp->flightCount; i++)
	{

	
	char* date;
	date = pComp->flightArr[i]->date.fullDate;
	NODE* pnode = (pComp->allDates).head.next;
	int check = 0;
	while (pnode != NULL)
	{
		if (strcmp((char*)pnode->key, date) == 0) {
			check++;
		}
		pnode = pnode->next;
	}
	if (check == 0)
	{
		pnode = L_insert(&pComp->allDates.head, date);
	}
	}
	//L_insert(pComp, date);
}
void writeCompanyToBinaryFile(FILE *file, Company *pComp)
{
	int nameLen = (int)strlen(pComp->name) + 1;
	fwrite(&nameLen, sizeof(int), 1, file);
	fwrite(pComp->name, sizeof(char), strlen(pComp->name) + 1, file);
	fwrite(&pComp->flightCount, sizeof(int), 1, file);
	for (int i = 0; i < pComp->flightCount; i++)
	{
		writeFlightToBinFile(file, pComp->flightArr[i]);
	}
	//fclose(file);
}

void SortFlightArr(Company* pComp)
{
	int stop = 0;
	
		int option = Companymenu();
		switch (option)
		{
		case eNotSort:
			pComp->bSearchPosabilty = 0;
			break;
		case eHour:
			qsort((pComp->flightArr), pComp->flightCount, sizeof(Flight*), CompareByHour);
			pComp->bSearchPosabilty = 1;
			break;

		case eDate:
			qsort((pComp->flightArr), pComp->flightCount, sizeof(Flight*), CompareByDate);
			pComp->bSearchPosabilty = 2;
			break;
		case eSourceCode:
			qsort((pComp->flightArr), pComp->flightCount, sizeof(Flight*), CompareBySourceCode);
			pComp->bSearchPosabilty = 3;
			break;

		case eDestCode:
			qsort((pComp->flightArr), pComp->flightCount, sizeof(Flight*), CompareDestCode);
			pComp->bSearchPosabilty = 4;
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	
}

void Search(Company* pComp) {
	int hour = 0;
	Flight* ap = (Flight*)malloc(sizeof(Flight));
	Flight** flight = NULL;
	switch (pComp->bSearchPosabilty)
	{
	case 1:
		do {
			hour=-1;
			printf("what flight hour you want search ");
			scanf("%d", &hour);
		} while (hour < 0 || hour>23);
		strcpy(ap->destCode,"");
		strcpy(ap->originCode ,"");
		*&ap->hour = hour;
		flight =(Flight**)(bsearch(&ap, (pComp->flightArr), pComp->flightCount, sizeof(Flight*), CompareByHour));
		freeFlight(ap);
		if (flight)
			printFlight(*flight);
		else
			printf("no result\n");
		break;
	case 2:
		printf("what code of date at flight you want search ");
		getCorrectDate(&ap->date);
		flight = (Flight**)(bsearch(&ap, (pComp->flightArr), pComp->flightCount, sizeof(Flight*), CompareByDate));
		freeFlight(ap);
		if (flight)
			printFlight(*flight);
		else
			printf("no result\n");
		break;
	case 3:
		printf("what code of src at flight you want search ");
		getAirportCode(ap->originCode);
		strcpy(ap->destCode,"XAX");
		*&ap->hour = hour;
		flight = (Flight**)(bsearch(&ap, (pComp->flightArr), pComp->flightCount, sizeof(Flight*), CompareBySourceCode));
		freeFlight(ap);
		if (flight)
			printFlight(*flight);
		else
			printf("no result\n");
		
		break;
	case 4:
		printf("what code of dest at flight you want search ");
		strcpy(ap->originCode,"XAX");
		getAirportCode(ap->destCode);
		*&ap->hour = hour;
		flight = (Flight**)(bsearch(&ap, (pComp->flightArr), pComp->flightCount, sizeof(Flight*), CompareDestCode));
		freeFlight(ap);
		if (flight)
			printFlight(*flight);
		else
			printf("no result\n");
		break;

	default:
		printf("sorry the array not sort so toy can do binary search\n");
		break;
	}
}






void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH+1];
	char codeDestination[CODE_LENGTH + 1];
	
	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n",codeOrigin, codeDestination);
}



void	printFlightArr(Flight** pFlight, int size)
{
	for (int i = 0; i < size; i++)
		printFlight(pFlight[i]);
}

void	freeFlightArr(Flight** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(arr[i]);
	}
}

void printDatesChar(const char* date) {
	printf("%s\n", date);
}

int Companymenu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, strCompany[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}