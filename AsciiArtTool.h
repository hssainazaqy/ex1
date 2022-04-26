
#ifndef HW1_ARCIIARTTOOL_H
#define HW1_ARCIIARTTOOL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <RLEList.h>

/*
* This is an Ascii Art compressing tool
* Uses:     
*       RLELists: a list containing a sequence of characters.
*
* The following functions are available:
*       RLEList asciiArtRead
*       RLEListResult asciiArtPrint
*       asciiArtPrintEncoded
*
*
*/
 
/*
* Compresses the file to an RLEList
* returns: 
*       an RLEList containing all of the file characters
*/
RLEList asciiArtRead(FILE* in_stream);


/*
* Writes an image according to the given RLEList to a given file
* returns: 
*       – RLE_LIST_NULL_ARGUMENT : if one of the arguments is NULL
*       - RLE_LIST_SUCCESS : writing succeeded
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/*
* Writes a compressed form of the given RLEList to a given file
* (similar to the return format of RLEListExportToString)
* returns: 
*       – RLE_LIST_NULL_ARGUMENT : if one of the arguments is NULL
*       - RLE_LIST_SUCCESS : writing succeeded
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif // HW1_ARCIIARTTOOL_H