
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int L_init(LIST* pList)
{
	if (pList == NULL) return 0;	// no list to initialize

	pList->head.next = NULL;
	return 1;
}

NODE* L_insert(NODE* pNode, void* Value)
{
	NODE* tmp;

	if (!pNode) return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}

int L_delete(NODE* pNode)
{
	NODE* tmp;

	if (!pNode || !(tmp = pNode->next)) return 0;

	pNode->next = tmp->next;
	free(tmp);
	return 1;
}


int L_free(LIST* pList, void(*freeFunc)(void*))
{
	NODE *tmp;

	if (!pList) return 0;

	for (tmp = &(pList->head); L_delete(tmp); );
	return 1;
}



int L_print(const LIST* pList, void(*print)(const void*))
{
	NODE	*tmp;
	int		c = 0;

	if ( !pList ) return 0;

	printf("\n");
	for ( tmp = pList->head.next;  tmp;  tmp = tmp->next, c++ )
		print(tmp->key);
	printf("\n");
	return c;
}
