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
char mapFunction (char c);
//--------------------------------------------------------
int main (int argc, char** argv)
{
    printf("part 0\n");
    char *flag = argv[FLAG];
    char *source = argv[SOURCE];
    char *target = argv[TARGET];
    printf("part 1\n");
    //---------------------------
    if(!flag||!source||!target){
        return -1;
    }
    printf("part 2\n");
    //---------------------------
    FILE* file_source = fopen(source,"r");
    printf("part 3\n");
    FILE* file_target = fopen(target,"w");
    printf("part 4\n");
    RLEList list = asciiArtRead(file_source);
    printf("part 5\n");
    //---------------------------
    if(!strcmp(flag,"-e")){

        RLEListResult result = asciiArtPrintEncoded(list,file_target);
        if(result != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            fclose(file_source);
            fclose(file_target);
            return -1;
        }

    }
    printf("part 6\n");
    //---------------------------
    if(!strcmp(flag,"-i")){

        RLEListResult result1 = RLEListMap(list,mapFunction);
        if(result1 != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            fclose(file_source);
            fclose(file_target);
            return -1;
        }
    printf("part 7\n");
        RLEListResult result2 = asciiArtPrint(list, file_target);
        printf("part asciiprint\n");
        if(result2 != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            fclose(file_source);
            fclose(file_target);
            return -1;
        }
    printf("part 8\n");
    }
    //---------------------------
    RLEListDestroy(list);
    fclose(file_source);
    fclose(file_target);
    //---------------------------
    return 0;
}
//--------------------------------------------------------
char mapFunction (char letter){
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