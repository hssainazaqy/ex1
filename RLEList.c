#include "RLEList.h"

typedef struct RLEList_t{
    char letter;
    struct *RLEList_t next;
}*RLEList;

//------------------------------------------------------
//--------------Implementations-------------------------
//------------------------------------------------------
RLEList RLEListCreate()
{	
    RLEList list = (int*)malloc(sizeof(*list));
    if(!list)
    {
	return NULL;
    }
    list->letter = '0';
    list->next = NULL;
    return list;	
}
//------------------------------------------------------
void RLEListDestroy(RLEList list){
    while(list){
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}
//------------------------------------------------------
RLEListResult RLEListAppend(RLEList list, char value)
{
    if(!list){return RLE_LIST_NULL_ARGUMENT;}

    RLEList newList = RLEListCreate();
    RLEList lastList = List;
    
    if(!newlist)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newList->Letter = value;
    while (!(lastList->next))
    {
	lastList = lastList->next;
    }
    lastList->next = newList;

    return RLE_LIST_SUCCESS;
}