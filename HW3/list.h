

#ifndef _LIST_
#define _LIST_



typedef struct node
{
	void*			key;
	struct node*	next;
}NODE;

typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

int L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, void* Value);	// add new node after *pNode

int L_delete(NODE* pNode);					// erase node after *pNode

int L_free(LIST* pList, void(*freeFunc)(void*));

int L_print(const LIST* pList, void(*print)(const void*));

#endif
