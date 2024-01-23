#include "phylib.h"

#include <stdint.h>
#include <stdlib.h>
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

double phylib_distance( phylib_object *obj1, phylib_object *obj2){
    //can assume obj1 is ALWAYS a rolling ball

    //get position of obj1
    phylib_coord ballPos = obj1->obj.rolling_ball.pos;

    //calculate distance based on what obj2 is
    switch (obj2->type){
        case PHYLIB_ROLLING_BALL:
        //auto moves to next case
        case PHYLIB_STILL_BALL: {
            //calc distance between centers and sub the diameter
            phylib_coord otherBallPos = obj2->obj.still_ball.pos;
            //Reference: https://www.ibm.com/docs/en/i/7.1?topic=functions-hypot-calculate-hypotenuse
            double distance = hypot( ballPos.x - otherBallPos.x, ballPos.y - otherBallPos.y);
            return (distance - PHYLIB_BALL_DIAMETER);
        }

        case PHYLIB_HOLE: {
            //calc distance between center of ball and hole then sub the hole_radius
            phylib_coord holePos = obj2->obj.hole.pos;
            double distance = hypot( ballPos.x - holePos.x, ballPos.y - holePos.y);
            return (distance - PHYLIB_HOLE_RADIUS);
        }

        case PHYLIB_HCUSHION: {
            //calc distance between ball and h cushion then sub ball radius
            //Reference: https://www.ibm.com/docs/en/i/7.4?topic=functions-fabs-calculate-floating-point-absolute-value
            double distance = fabs(ballPos.y - obj2->obj.hcushion.y);
            return (distance - PHYLIB_BALL_RADIUS);
        }

        case PHYLIB_VCUSHION: {
            //calc distance between ball and h cushion then sub ball radius
            //Reference: https://www.ibm.com/docs/en/i/7.4?topic=functions-fabs-calculate-floating-point-absolute-value
            double distance = fabs(ballPos.x - obj2->obj.vcushion.x);
            return (distance - PHYLIB_BALL_RADIUS);
        }

        default:
            return -1.0; //obj2 isnt valid type
    }
}
