#include <RLEList.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

//------------------------------------------------------
//--------------Implementations-------------------------
//------------------------------------------------------

RLEList asciiArtRead(FILE* in_stream){
    RLEList new_list = RLEListCreate();
    FILE* ptr = in_stream;
    char curr_letter;

    if(!new_list ||!ptr){
        return NULL;
    }

    //RLEList tmp_list = new_list;
    RLEListResult result = RLE_LIST_SUCCESS;

    //int stop = 0;
    while(curr_letter!= EOF){
        //stop = fscanf((ptr),"%c",&curr_letter);
        curr_letter = fgetc(ptr);
        result = RLEListAppend(new_list, curr_letter);
        if(result!= RLE_LIST_SUCCESS){
            return NULL;
        }
    }
    return new_list;
}
//------------------------------------------------------
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream){
    if(!list||!out_stream){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tmp_list = list;
    int size = RLEListSize(tmp_list);
    FILE* ptr = out_stream;
    char curr_letter;
    RLEListResult res = RLE_LIST_SUCCESS;
    RLEListResult *result = &res;
    for(int i = 0; i < size; i++){
        curr_letter = RLEListGet(tmp_list, i, result);
        if(*result == RLE_LIST_SUCCESS){
            fprintf(ptr, "%c", curr_letter);
        }
        else{
            return result;
        }
    }
    return RLE_LIST_SUCCESS;
}
//------------------------------------------------------
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream){
     if(!list){
         return RLE_LIST_NULL_ARGUMENT;
     }
     RLEListResult res = RLE_LIST_SUCCESS;
     RLEListResult *result = &res;
     char* tmp_str = RLEListExportToString(list, result);
     if(*result == RLE_LIST_NULL_ARGUMENT){
         return RLE_LIST_NULL_ARGUMENT;
     }
     FILE* ptr = out_stream;
     int len_str = strlen(tmp_str);
     for(int i = 0; i < len_str; i++){
         fprintf(ptr, "%c", tmp_str[i]);
     }
     free(tmp_str);
     return RLE_LIST_SUCCESS;
 }
//------------------------------------------------------
