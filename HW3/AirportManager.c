#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	int count=0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count);
	} while (count < 0);
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;

	L_init(&pManager->arr);

	Airport* ap;
	for (int i = 0; i < count; i++)
	{
		NODE* pnode = &pManager->arr.head;
		ap = (Airport*)malloc(sizeof(Airport));
		if (!ap)
			return 0;
		setAirport(ap, pManager);
		int x = 0;
		while (pnode->next!=NULL)
		{
			pnode = pnode->next;
			x += reorder((Airport*)pnode->key, ap);
		}
		if (x == 0) {
			L_insert(&pManager->arr.head, ap);
		}
		else
		{
			NODE* pnode = &pManager->arr.head;
			while (x!=0)
			{
			pnode = pnode->next;
			x--;
			}
			L_insert(pnode, ap);
		}
		
		


	//	while (pnode->next != NULL && x != -1){
	//		pnode = pnode->next;
	//		x=reorder((Airport*)pnode->key, ap);
	//	} 
	//	if (x==1)
	//	{
	//		L_insert(&pManager->arr.head, ap);
	//	}
	//	else {
	//		pnode = L_insert(pnode, ap);
	//	}
		pManager->count++;
	}
	return 1;
}

int reorder(Airport* pPort1, Airport* pPort2) {
	if (strcmp(pPort1->code, pPort2->code) == -1)
		return 1;
	else
	{
		return 0;
	}
}


FILE* FileOpen()
{
	FILE* f = fopen("airport_authority.txt", "w");
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return NULL;
	}
	return f;
}
void fError(FILE* f)
{
	f = fopen("myfile.txt", "r");
	if (f == NULL)
	{
		printf("Error opening file\n");
		return;
	}

	fputc('x', f);
	if (ferror(f))
		printf("Error Writing to myfile.txt\n");

}
void initAirportManagerFromTextFile(FILE* file, AirportManager* pManager)
{

	pManager->count = 0;
	L_init(&(pManager->arr));
	int numOfAirpoets;
	readIntFromTextFile(file, &numOfAirpoets);
	for (int i = 0; i < numOfAirpoets; i++)
	{
		Airport* airport = (Airport*)malloc(sizeof(Airport));
		if (!airport)
			return ;
		if (readAirportFromTextFile(file, airport) == 0)
		{
			return;
		}
		NODE* pnode = &pManager->arr.head;
		int x = 0;
		while (pnode->next!=NULL)
		{
			pnode = pnode->next;
			x += reorder((Airport*)pnode->key, airport);
		}
		if (x == 0) {
			L_insert(&pManager->arr.head, airport);
		}
		else
		{
			NODE* pnode = &pManager->arr.head;
			while (x!=0)
			{
			pnode = pnode->next;
			x--;
			}
			L_insert(pnode, airport);
		}
		pManager->count++;
	}
}

void writeToFile(FILE* f, AirportManager* aPM)
{
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}
	fprintf(f, "%d\n", aPM->count);
	Airport* ap = (Airport*)malloc(sizeof(Airport));
	NODE* ptr = aPM->arr.head.next;
	for (int i = 0; i < aPM->count; i++)
	{
		ap = ptr->key;
		fprintf(f, "%s\n%s\n%s\n", ap->name, ap->country, ap->code);
		ptr = ptr->next;
	}

}

int	addAirport(AirportManager* pManager)
{
	if (pManager->count==0) {
		L_init(&pManager->arr);
	}
	NODE* pnode = &pManager->arr.head;
	int x = 0;
	Airport* ap;
	ap = (Airport*)malloc(sizeof(Airport));
	if (!ap)
		return 0;
	setAirport(ap, pManager);
	while (pnode->next != NULL && x != -1) {
		pnode = pnode->next;
		x = reorder((Airport*)pnode->key, ap);
	}
	if (x == 1)
	{
		L_insert(&pManager->arr.head, ap);
	}
	else {
		pnode = L_insert(pnode, ap);
	}
	pManager->count++;
	return 1;
}

void  setAirport(Airport* pPort, AirportManager* pManager)//NODE* pnode
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}
	initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	NODE* pnode;
	if (!&(pManager->arr))
		return NULL;
	pnode = (pManager->arr).head.next;
	while (pnode != NULL){
		if (isAirportCode((Airport*)pnode->key, code))
			return pnode->key;
		pnode = pnode->next;
	}
	return NULL;
}



int checkUniqeCode(const char* code,const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

void	printAirports(const AirportManager* pManager)
{
	printf("there are %d airports\n", pManager->count);
	L_print(&pManager->arr, printAirport);
}

void	freeManager(AirportManager* pManager)
{
	L_free(&pManager->arr, freeAirport);
}
