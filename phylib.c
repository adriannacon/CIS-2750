#include "phylib.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

void phylib_copy_object(phylib_object **dest, phylib_object **src){
    if (*src == NULL){ //check if src points to NULL
        *dest = NULL; //sets dest to NULL
    } else{
        //allocate mem for the new obj
        *dest = (phylib_object *)malloc(sizeof(phylib_object));

        //check if malloc worked
        if (*dest == NULL){
            *dest = NULL; //dest set to NULL
        } else{
            //memcpy the contents of obj
            //Reference: https://cplusplus.com/reference/cstring/memcpy/
            memcpy(*dest, *src, sizeof(phylib_object));
        }
    }
}

phylib_table *phylib_copy_table( phylib_table *table){
    if (table == NULL){ //check if inputted table is NULL
        return NULL; //nothing to copy
    }

    //allocate mem for new table
    phylib_table *copiedTable = (phylib_table *)malloc(sizeof(phylib_table));

    //check mem allocation
    if (copiedTable != NULL){
       //Reference: https://cplusplus.com/reference/cstring/memcpy/
        memcpy(copiedTable, table, sizeof(phylib_table));
    }

    return copiedTable; //return copied table
}