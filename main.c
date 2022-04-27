#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define FLAG 1
#define SOURCE 2
#define TARGET 3
#define EMPTY_SPACE ' '
#define AT_SIGN '@'
//-------------------------------------------
char MapFunction (char c);
//--------------------------------------------------------
int main (int argc, char** argv)
{
    char *flag = argv[FLAG];
    char *source = argv[SOURCE];
    char *target = argv[TARGET];
    //---------------------------
    if(!flag||!source||!target){
        return -1;
    }
    //---------------------------
    fopen(source,"r");
    fopen(target,"w");
    RLEList list = asciiArtRead(source);
    //---------------------------
    if(!strcmp(flag,"-e")){

        RLEListResult result = asciiArtPrintEncoded(list,target);
        if(result != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            fclose(source);
            fclose(target);
            return -1;
        }

    }

    if(!strcmp(flag,"-i")){

        RLEListResult result1 = RLEListMap(list,MapFunction);
        if(result1 != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            fclose(source);
            fclose(target);
            return -1;
        }

        RLEListResult result2 = asciiArtPrint(list, target);
        if(result2 != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            fclose(source);
            fclose(target);
            return -1;
        }
    }
    RLEListDestroy(list);
    fclose(source);
    fclose(target);
    return 0;
}
//--------------------------------------------------------
char MapFunction (char letter){

    if(letter == EMPTY_SPACE){
        return AT_SIGN;
    }
    //-------------------
    if(letter == AT_SIGN){
        return EMPTY_SPACE;
    }
    //-------------------
    return letter;
}
//--------------------------------------------------------