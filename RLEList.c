#include <RLEList.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

typedef struct RLEList_t{

    char letter;
    int appeared;
    struct RLEList_t *next;

} RLEList_t;

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
    while(list){
        RLEList toDelete = list;
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

    RLEList lastNode = list;

    while (lastNode->next){
	    lastNode = lastNode->next;
    }

    if(lastNode->letter == value){
        lastNode->appeared++;
    }
    else{
        RLEList newNode = RLEListCreate();
        if(!newNode){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newNode->letter = value;
        lastNode->next = newNode;
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
    RLEList curr = list;

    while (curr){
        counter += curr->appeared;
        curr = curr->next;
    }
    return counter;
}
//------------------------------------------------------
RLEListResult RLEListRemove(RLEList list, int index)
{
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(index >= RLEListSize(list)){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    RLEList temp_list = list;
    int indexes_left = index;
    //----------head case------------
    if(temp_list->appeared > indexes_left){
        if(temp_list->appeared == 1){
            list = list->next;
            free(temp_list);
        }
        else{
            temp_list->appeared--;
        }
        return RLE_LIST_SUCCESS;
    }
    //----------rest case------------
    RLEList prev = list;
    indexes_left -= prev->appeared;
    temp_list = temp_list->next; 
    while(temp_list){
        if(indexes_left +1 > (temp_list->appeared))
        {
            indexes_left -= temp_list->appeared;
            temp_list = temp_list->next;
            prev = prev->next;
        }
        else{
            if(temp_list->appeared > 1)
            {
                temp_list->appeared--;
            }
            else{

                    if(prev->letter == temp_list->next->letter)
                    {
                        prev->appeared += temp_list->next->appeared;
                        prev->next= temp_list->next->next;
                        free(temp_list);
                        return RLE_LIST_SUCCESS;
                    }
                    else{
                         prev->next= temp_list->next;
                        free(temp_list);
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

    RLEList temp_list = list;

    while(temp_list)
    {
        temp_list->letter = map_function(temp_list->letter);
        temp_list = temp_list->next;
    }
    return RLE_LIST_SUCCESS;
}
//------------------------------------------------------
char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }

    if(RLEListSize(list) <= index)
     {
         *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
         return 0;
     }

    int counter = index;
    RLEList temp_list = list;
    char wanted;

    while(temp_list)
    {
        if(temp_list->appeared > counter){
            wanted = temp_list->letter;
            *result = RLE_LIST_SUCCESS;
            return wanted;
        }
        else{
            counter -= temp_list->appeared;
            temp_list = temp_list->next;
        }
    }
    *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    return 0;
}
//------------------------------------------------------
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int size = RLEListSize(list);
    char* newString = (char*) malloc(sizeof(char)*size+1);

    if(!newString)
    {
        free(newString);
        return NULL;
    }

    int index = 0;

while(list){
        newString[index] = list->letter;
        index++;
        sprintf(newString+index, "%c", list->appeared);
        newString[++index] = '\n';
        list = list->next;
        index++;
    }

    newString[++index] = '\0';
    *result = RLE_LIST_SUCCESS;
    
    return newString;
}
//------------------------------------------------------

