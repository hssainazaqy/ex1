#include <RLEList.h>
#include <stdlib.h>
#include <string.h>
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
    RLEList tmp_list = new_list;
    int index = 0;
    while(curr_letter != EOF){
        //fscanf((ptr+index),"%c",curr_letter);
        curr_letter = fgetc(ptr+index);
        RLEListAppend(tmp_list, curr_letter);
        index++;      
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
        if(*result != RLE_LIST_SUCCESS){
            fprintf(ptr+i, "%c", curr_letter);
        }
        else{
            printf("result in asciiArtPrint wasnt success, check RLEListGet \n");
            return RLE_LIST_ERROR;
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
         fprintf(ptr+i, "%c", tmp_str[i]);
     }
     return RLE_LIST_SUCCESS;
 }
//------------------------------------------------------