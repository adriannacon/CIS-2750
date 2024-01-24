#include "phylib.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Part I Functions!

phylib_object *phylib_new_still_ball( unsigned char number, phylib_coord *pos){
    //allocate mem
    phylib_object *newSBall = (phylib_object *)malloc(sizeof(phylib_object));

    //check if NULL
    if ( newSBall == NULL){
        return NULL; //if malloc fails
    }

    //set type
    newSBall->type = PHYLIB_STILL_BALL;

    //set info
    newSBall->obj.still_ball.number = number;
    newSBall->obj.still_ball.pos = *pos;

    return newSBall; //return the pter
}

phylib_object *phylib_new_rolling_ball( unsigned char number, phylib_coord *pos, phylib_coord *vel, phylib_coord *acc){
    //allocate mem
    phylib_object *newRBall = (phylib_object *)malloc(sizeof(phylib_object));

    //check if NULL
    if ( newRBall == NULL){
        return NULL; //if malloc fails
    }

    //set type
    newRBall->type = PHYLIB_ROLLING_BALL;

    //set info
    newRBall->obj.rolling_ball.number = number;
    newRBall->obj.rolling_ball.pos = *pos;
    newRBall->obj.rolling_ball.vel = *vel;
    newRBall->obj.rolling_ball.acc = *acc;

    return newRBall; //return the pter
}

phylib_object *phylib_new_hole( phylib_coord *pos){
    //allocate mem
    phylib_object *newHole = (phylib_object *)malloc(sizeof(phylib_object));

    //check if NULL
    if ( newHole == NULL){
        return NULL; //if malloc fails
    }

    //set type
    newHole->type = PHYLIB_HOLE;

    //set info
    newHole->obj.hole.pos = *pos;

    return newHole; //return the pter
}

phylib_object *phylib_new_hcushion( double y){
    //allocate mem
    phylib_object *newHCushion = (phylib_object *)malloc(sizeof(phylib_object));

    //check if NULL
    if ( newHCushion == NULL){
        return NULL; //if malloc fails
    }

    //set type
    newHCushion->type = PHYLIB_HCUSHION;

    //set info
    newHCushion->obj.hcushion.y = y;

    return newHCushion; //return the pter
}

phylib_object *phylib_new_vcushion( double x){
    //allocate mem
    phylib_object *newVCushion = (phylib_object *)malloc(sizeof(phylib_object));

    //check if NULL
    if ( newVCushion == NULL){
        return NULL; //if malloc fails
    }

    //set type
    newVCushion->type = PHYLIB_VCUSHION;

    //set info
    newVCushion->obj.vcushion.x = x;

    return newVCushion; //return the pter
}

phylib_table *phylib_new_table( void){
    //allocate mem
    phylib_table *newTable = (phylib_table *)malloc(sizeof(phylib_table));

    //check if NULL
    if ( newTable == NULL){
        return NULL; //if malloc fails
    }

    //set time to 0.0
    newTable->time = 0.0;

    //initalize ALL obj array elements to NULL
    for (int i =0; i < PHYLIB_MAX_OBJECTS; i++){
        newTable->object[i] = NULL;
    }

    //add elements using above phylib_new_<obj> fns
    //4 CUSHIONS
    newTable->object[0] = phylib_new_hcushion(0.0); //horizontal cushion at y=0.0
    newTable->object[1] = phylib_new_hcushion(PHYLIB_TABLE_LENGTH); //horizontal cushion at y=2700.0
    newTable->object[2] = phylib_new_vcushion(0.0); //horizontal cushion at x=0.0
    newTable->object[3] = phylib_new_vcushion(PHYLIB_TABLE_WIDTH); //horizontal cushion at x=1350.0

    //6 HOLES
    newTable->object[4] = phylib_new_hole(&(phylib_coord){0.0, 0.0}); //Top L hole
    newTable->object[5] = phylib_new_hole(&(phylib_coord){0.0, PHYLIB_TABLE_WIDTH}); //Mid L hole
    newTable->object[6] = phylib_new_hole(&(phylib_coord){0.0, PHYLIB_TABLE_LENGTH}); //Bottom L hole
    newTable->object[7] = phylib_new_hole(&(phylib_coord){PHYLIB_TABLE_WIDTH, 0.0}); //Top R hole
    newTable->object[8] = phylib_new_hole(&(phylib_coord){PHYLIB_TABLE_WIDTH, PHYLIB_TABLE_WIDTH}); //Mid R hole
    newTable->object[9] = phylib_new_hole(&(phylib_coord){PHYLIB_TABLE_WIDTH, PHYLIB_TABLE_LENGTH}); //Bottom R hole

    return newTable;
}

//PART II Functions!

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

//PART 3 Functions!

void phylib_roll( phylib_object *new, phylib_object *old, double time){
    if (new == NULL || old == NULL){ //check if inputted object is NULL
        return; //do nothing
    }

    if (new->type != PHYLIB_ROLLING_BALL || old->type != PHYLIB_ROLLING_BALL){ //check if inputted ball is rolling
        return; //do nothing
    }

    //p = p1 + v1t + 0.5a1t^2
    //position update for x direction
    double xPos = old->obj.rolling_ball.pos.x + (old->obj.rolling_ball.vel.x*time) + (0.5)*old->obj.rolling_ball.acc.x*(time*time);
    new->obj.rolling_ball.pos.x = xPos;

    //position update for y direction
    double yPos = old->obj.rolling_ball.pos.y + (old->obj.rolling_ball.vel.y*time) + (0.5)*old->obj.rolling_ball.acc.y*(time*time);
    new->obj.rolling_ball.pos.y = yPos;

    //v = v1 + a1t
    //velocity update for x direction
    double xVel = old->obj.rolling_ball.vel.x + (old->obj.rolling_ball.vel.x*time);
    new->obj.rolling_ball.vel.x = xVel;

    //velocity update for y direction
    double yVel = old->obj.rolling_ball.vel.y + (old->obj.rolling_ball.vel.y*time);
    new->obj.rolling_ball.vel.y = yVel;

    //check for x velocity sign change by multiplying new and old vels if neg then need to set to 0.0
    //Reference: this method was discussed in class by Dr. Stefan Kremer
    if ((new->obj.rolling_ball.vel.x*old->obj.rolling_ball.vel.x) < 0.0){
        new->obj.rolling_ball.vel.x = 0.0; //sets x velocity to 0.0
        new->obj.rolling_ball.acc.x = 0.0;  //sets x acceleration to 0.0
    }

    //check for y velocity sign change by multiplying new and old vels if neg then need to set
    //Reference: this method was discussed in class by Dr. Stefan Kremer
    if ((new->obj.rolling_ball.vel.y*old->obj.rolling_ball.vel.y) < 0.0){
        new->obj.rolling_ball.vel.y = 0.0; //sets x velocity to 0.0
        new->obj.rolling_ball.acc.y = 0.0;  //sets x acceleration to 0.0
    }
}

unsigned char phylib_stopped( phylib_object *object){
    if (object == NULL){ //check if null
        return 0; ///did not convert ball bc DNE
    }
    
    
    if (object->type != PHYLIB_ROLLING_BALL){ //check if obj is a rolling ball
        return 0; //did not convert ball bc already still ball
    }
}

void phylib_bounce( phylib_object **a, phylib_object **b){

}

unsigned char phylib_rolling( phylib_table *t){

}

phylib_table *phylib_segment( phylib_table *table){


}

