#include <RLEList.h>
#include <stdlib.h>
#include <stdbool.h>

//------------------------------------------------------
//--------------Implementations-------------------------
//------------------------------------------------------

RLEList asciiArtRead(FILE* in_stream){
    RLEList new_list = RLEListCreate();
    FILE* ptr = in_stream;
    char curr_letter;

    if(!new_list){
        return NULL;
    }

    RLEList tmp_list = new_list;
    curr_letter == fgetc(ptr);

    while(curr_letter != EOF){
        ptr++;
        curr_letter = fgetc(ptr);

        if(curr_letter == tmp_list->letter){
            tmp_list->apperead++;
        }
        else if (curr_letter==NULL){
            break;
        }
        else{
            RLEListAppend(tmp_list, curr_letter);
            tmp_list = tmp_list->next;
            tmp_list->letter = curr_letter;
            tmp_list->apperead++;
        }        
    }
    return new_list;
}
//------------------------------------------------------

//------------------------------------------------------
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream){
     if(!list){
         return RLE_LIST_NULL_ARGUMENT;
     }
     RLEListResult* result;
     char* tmp_str = RLEListExportToString(list, result);
     FILE* ptr = out_stream;
     int len_str = strlen(tmp_str);
     for(int i = 0; i < len_str; i++){
         fprintf(ptr, "%c", tmp_str[i]);
     }
     return RLE_LIST_SUCCESS;
 }
//------------------------------------------------------