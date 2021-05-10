#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	LIST		allDates;
	int			bSearchPosabilty;
}Company;

void	initCompany(Company* pComp);
int		addFlight(Company* pComp,const AirportManager* pManager);
void	printCompany(const Company* pComp);
void	printFlightsCount(const Company* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	freeFlightArr(Flight** arr, int size);
void	freeCompany(Company* pComp);
void	printDatesChar(const char* date);
void	SortFlightArr(Company* pComp);
void	Search(Company* pComp);
void	addFlightDateToDateList(Company* pComp);
void	writeCompanyToBinaryFile(FILE *file, Company *pComp);
void initCompanyFromBinaryFile(FILE* file, Company* pComp);
#endif

