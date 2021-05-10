#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "list.h"
typedef struct
{
	LIST	arr;
	int			count;
}AirportManager;

int		initManager(AirportManager* pManager);
int		addAirport(AirportManager* pManager);
void	setAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const AirportManager* pManager);
void	freeManager(AirportManager* pManager);
void writeToFile(FILE* f, AirportManager* aPM);
void initAirportManagerFromTextFile(FILE* file, AirportManager* pManager);
void fError(FILE* f);
int reorder(Airport* pPort1, Airport* pPort2);
FILE* FileOpen();
#endif