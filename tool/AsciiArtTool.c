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
    printf("part 9\n");
    FILE* ptr = in_stream;
    char curr_letter;
    if(!new_list ||!ptr){
        return NULL;
    }
    printf("part 10\n");
    RLEList tmp_list = new_list;
    int stop = 0;
    while(stop != EOF){
        stop = fscanf((ptr),"%c",&curr_letter);
        printf("part 11\n");
        RLEListAppend(tmp_list, curr_letter);
        printf("part 12\n");     
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
        printf("part got letter\n");
        if(*result == RLE_LIST_SUCCESS){
            fprintf(ptr+i, "%c", curr_letter);
        printf("part asciiArtPrint printed letter\n");
        }
        else{
        printf("result in asciiArtPrint wasnt success, check RLEListGet \n");
            return RLE_LIST_ERROR;
        }
    }
        printf("part RLEListGet ended in asciiArtPrint?\n");
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
         fprintf(ptr+i, "%c", tmp_str[i]);
     }
     return RLE_LIST_SUCCESS;
 }
//------------------------------------------------------
