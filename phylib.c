#include "phylib.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void phylib_copy_object( phylib_object **dest, phylib_object **src){
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

void phylib_add_object( phylib_table *table, phylib_object *object){
    if (table == NULL || object == NULL){ //check if inputted table or obj is NULL
        return; //do nothing
    }

    //iterate over the obj array until NULL 
    for (int i =0; i < PHYLIB_MAX_OBJECTS; i++){
        if (table->object[i] == NULL){
            //assign to the address of the obj
            table->object[i] = object;
            //object added
            return; //exit
        }
    }

    //if no null pointer-> do nothing
}

void phylib_free_table( phylib_table *table){
    if (table == NULL){ //check if inputted table is NULL
        return; //do nothing
    }

    //free every non-NULL pter in obj array
    for (int i =0; i < PHYLIB_MAX_OBJECTS; i++){
        if (table->object[i] != NULL){
            free(table->object[i]); //free the obj
            table->object[i] = NULL; //set to NULL
        }
    }

    //free whole table
    free(table);
}

phylib_coord phylib_sub( phylib_coord c1, phylib_coord c2){
    phylib_coord result;

    //calculate the differences
    result.x = c1.x - c2.x; //x coord
    result.y = c1.y - c2.y; //y coord

    return result;
}

double phylib_length( phylib_coord c){
    //calculate length w Pythagorean Theorm -> z^2 = x^2 + y^2
    double x_sqred = c.x*c.x;
    double y_sqred = c.y*c.y;

    //Reference: https://www.upgrad.com/tutorials/software-engineering/c-tutorial/sqrt-in-c/#:~:text=In%20C%20programming%20the%20square,h%3E%20header%20file.
    double length = sqrt(x_sqred + y_sqred);

    return length;
}

double phylib_dot_product( phylib_coord a, phylib_coord b){
    //Reference: utilized understanding from CIS*2750 Lab 1
    double dotProduct = (a.x*b.x) + (a.y*b.y);

    return dotProduct;
}