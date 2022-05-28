#include "RLEList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

struct RLEList_t{

    char letter;
    int appeared;
    RLEList next;

};

#define THREE 3
//------------------------------------------------------
//--------------Implementations-------------------------
//------------------------------------------------------
RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list)); 

    if(!list)
    {
        free(list);
	    return NULL;
    }

    list->letter = '\0';
    list->appeared = 0;
    list->next = NULL;
    
    return list;
}
//------------------------------------------------------
void RLEListDestroy(RLEList list){
    RLEList toDelete;
    while(list){
        toDelete = list;
        list = list->next;
        free(toDelete);
    }
}
//------------------------------------------------------
RLEListResult RLEListAppend(RLEList list, char value)
{
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }


    while (list->next){
	    list = list->next;
    }
    
    if(list->letter == value){
        list->appeared++;
    }
    else if(list->letter == '\0'){
        list->letter = value;
        list->appeared = 1;
    }
    else{
        RLEList newNode = RLEListCreate();
        if(!newNode){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newNode->letter = value;
        newNode->appeared = 1;
        list->next = newNode;
    }
    

    return RLE_LIST_SUCCESS;
}
//------------------------------------------------------
int RLEListSize(RLEList list)
{
    if(!list){
        return -1;
    }

    int counter = 0;

    while (list){

        counter += list->appeared;
        list = list->next;
    }

    return counter;
}
//------------------------------------------------------
RLEListResult RLEListRemove(RLEList list, int index)
{
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index >= RLEListSize(list)||index < 0){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    int indexes_left = index;
    //----------head case------------
    if(list->appeared > indexes_left){
        if(list->appeared == 1){
            RLEList tmplist = list;
            list = list->next;
            free(tmplist);
        }
        else{
            list->appeared--;
        }
        return RLE_LIST_SUCCESS;
    }
    //----------rest case------------
    RLEList prev = list;
    indexes_left -= prev->appeared;
    list = list->next; 

    while(list){
        if(indexes_left +1 > (list->appeared)){
            indexes_left -= list->appeared;
            list = list->next;
            prev = prev->next;
        }
        else{
            if(list->appeared > 1){
                list->appeared--;
            }
            else{
                    if(prev->letter == list->next->letter){
                        prev->appeared += list->next->appeared;
                        prev->next= list->next->next;
                        free(list);
                        return RLE_LIST_SUCCESS;
                    }
                    else{
                        prev->next= list->next;
                        free(list);
                        return RLE_LIST_SUCCESS;
                    }
            }
        }
    }
    return RLE_LIST_ERROR;//not supposed to get here
}
//------------------------------------------------------
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list)
    {
        list->letter = map_function(list->letter);
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}
//------------------------------------------------------

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return '\0';
    }

    if(RLEListSize(list) <= index || index <0)
     {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return '\0';
    }

    bool canReturnResult = (result!=NULL);
    int counter = 0;
    char wanted = '\0';
    while(list){
        counter += list->appeared;
        if(counter>index){
            wanted = list->letter;
            break;
        }
        list = list->next;
    }
    if(canReturnResult){
        *result = RLE_LIST_SUCCESS;
    }
    return wanted;
}
//------------------------------------------------------
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int size = RLEListSize(list);
    char* newString = (char*) malloc(sizeof(char)*(size*THREE+1));

    if(!newString)
    {
        free(newString);
        return NULL;
    }
    //-------------------------------
    RLEList temp_list = list;
    int node_len = 0;
    char *currNodeptr = newString;

    newString[0] = '\0';
    while(temp_list){
        node_len++;
        temp_list = temp_list->next;
    }
    //--------------------------------
    for (int i = 0 ; i < node_len-1; i++){
        int numOfChars = 0;
        numOfChars = sprintf(currNodeptr,"%c%d\n", list->letter,list->appeared);
        currNodeptr += numOfChars;
        list= list->next;
    }

    if(result){
        *result = RLE_LIST_SUCCESS;
    }
    
    return newString;
}
//------------------------------------------------------
