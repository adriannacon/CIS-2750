//written by Adrianna Con 

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
    
    //check table
    if (copiedTable == NULL){
        return NULL;
    }

    //copy time 
    copiedTable->time = table->time;
    for (int i = 0; i < PHYLIB_MAX_OBJECTS; i++){
        if(table->object[i] != NULL){ //if obj exists
            phylib_copy_object(&(copiedTable->object[i]), &(table->object[i]));
        } else{ //set to NULL
            copiedTable->object[i] = NULL;
        }
    }

    return copiedTable; //return copied table
}

void phylib_add_object( phylib_table *table, phylib_object *object){
    if (table == NULL || object == NULL){ //check if inputted table or obj is NULL
        return; //do nothing
    }

    //iterate over the obj array until NULL 
    for (int i = 0; i < PHYLIB_MAX_OBJECTS; i++){
        if (table->object[i] == NULL){
            //assign to the address of the obj
            table->object[i] = object;
            //object added
            break; //leave if statement
        }
    }

    //if no NULL pointer-> do nothing
}

void phylib_free_table( phylib_table *table){
    if (table == NULL){ //check if inputted table is NULL
        return; //do nothing
    }

    //free every non-NULL pter in obj array
    for (int i = 0; i < PHYLIB_MAX_OBJECTS; i++){
        if (table->object[i] != NULL){
            //printf("freeing object %d", i);
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
    double x_sqred = c.x * c.x;
    double y_sqred = c.y * c.y;

    //Reference: https://www.upgrad.com/tutorials/software-engineering/c-tutorial/sqrt-in-c/#:~:text=In%20C%20programming%20the%20square,h%3E%20header%20file.
    double length = sqrt(x_sqred + y_sqred);

    return length;
}

double phylib_dot_product( phylib_coord a, phylib_coord b){
    //Reference: utilized understanding from CIS*2750 Lab 1
    double dotProduct = (a.x * b.x) + (a.y * b.y);

    return dotProduct;
}

double phylib_distance( phylib_object *obj1, phylib_object *obj2){
    //can assume obj1 is ALWAYS a rolling ball

    if (obj1 == NULL || obj2 == NULL) {
        // Handle the case where obj1 or obj2 is NULL
        return -1.0; // or another appropriate value
    }   

    //get position of obj1
    phylib_coord aPos = obj1->obj.rolling_ball.pos;

    //calculate distance based on what obj2 is
    double distance = 0.0;
    
    switch (obj2->type){
        case PHYLIB_ROLLING_BALL:
        //auto moves to next cade
        case PHYLIB_STILL_BALL:
            //calc distance between centers and sub the diameter
            //Reference: https://www.ibm.com/docs/en/i/7.1?topic=functions-hypot-calculate-hypotenuse
            distance = hypot( aPos.x - obj2->obj.still_ball.pos.x, aPos.y - obj2->obj.still_ball.pos.y);
            distance = distance - PHYLIB_BALL_DIAMETER;
            break;

        case PHYLIB_HOLE: {
            //calc distance between center of ball and hole then sub the hole_radius
            distance = hypot( aPos.x - obj2->obj.hole.pos.x, aPos.y - obj2->obj.hole.pos.y);
            distance = distance - PHYLIB_HOLE_RADIUS;
            break;
        }

        case PHYLIB_HCUSHION: {
            //calc distance between ball and h cushion then sub ball radius
            //Reference: https://www.ibm.com/docs/en/i/7.4?topic=functions-fabs-calculate-floating-point-absolute-value
            distance = fabs(aPos.y - obj2->obj.hcushion.y);
            distance = distance - PHYLIB_BALL_RADIUS;
            break;
        }

        case PHYLIB_VCUSHION: {
            //calc distance between ball and h cushion then sub ball radius
            //Reference: https://www.ibm.com/docs/en/i/7.4?topic=functions-fabs-calculate-floating-point-absolute-value
            distance = fabs(aPos.x - obj2->obj.vcushion.x);
            distance = distance - PHYLIB_BALL_RADIUS;
            break;
        }

        default:
            return -1.0; //obj2 isnt valid type
    }

    //Reference: https://www.geeksforgeeks.org/conditional-or-ternary-operator-in-c/
    return (distance > 0) ? distance : -1.0; //only returns distance if not negative
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
    new->obj.rolling_ball.pos.x = old->obj.rolling_ball.pos.x + (old->obj.rolling_ball.vel.x * time) + (0.5 * old->obj.rolling_ball.acc.x * time * time);
    //position update for y direction
    new->obj.rolling_ball.pos.y = old->obj.rolling_ball.pos.y + (old->obj.rolling_ball.vel.y * time) + (0.5 * old->obj.rolling_ball.acc.y * time * time);

    //v = v1 + a1t
    //velocity update for x direction
    new->obj.rolling_ball.vel.x = old->obj.rolling_ball.vel.x + old->obj.rolling_ball.acc.x * time;
    //velocity update for y direction
    new->obj.rolling_ball.vel.y = old->obj.rolling_ball.vel.y + old->obj.rolling_ball.acc.y * time;

    //printf( "ROLLING_BALL OLD X ACC IN ROLL FN (%6.1lf)", old->obj.rolling_ball.acc.x);
    //printf( "ROLLING_BALL OLD Y ACC IN ROLL FN (%6.1lf)", old->obj.rolling_ball.acc.y);

    //check for x velocity sign change by multiplying new and old vels if neg then need to set to 0.0
    //Reference: this method was discussed in class by Dr. Stefan Kremer
    if ((new->obj.rolling_ball.vel.x * old->obj.rolling_ball.vel.x) < 0.0){
        new->obj.rolling_ball.vel.x = 0.0; //sets x velocity to 0.0
        new->obj.rolling_ball.acc.x = 0.0;  //sets x acceleration to 0.0
    }

    //check for y velocity sign change by multiplying new and old vels if neg then need to set
    //Reference: this method was discussed in class by Dr. Stefan Kremer
    if ((new->obj.rolling_ball.vel.y * old->obj.rolling_ball.vel.y) < 0.0){
        new->obj.rolling_ball.vel.y = 0.0; //sets x velocity to 0.0
        new->obj.rolling_ball.acc.y = 0.0;  //sets x acceleration to 0.0
    }
}

unsigned char phylib_stopped( phylib_object *object){
    if (object == NULL){ //check if NULL
        return 0; ///did not convert ball bc DNE
    }
    
    if (object->type != PHYLIB_ROLLING_BALL){ //check if obj is a rolling ball
        return 0; //did not convert ball bc already still ball
    }

    //calculate speed -> length of its velocity
    double speed = phylib_length(object->obj.rolling_ball.vel);

    //check speed against epsilon
    if (speed < PHYLIB_VEL_EPSILON){
        object->type = PHYLIB_STILL_BALL;
        object->obj.still_ball.number = object->obj.rolling_ball.number; //converts number
        object->obj.still_ball.pos = object->obj.rolling_ball.pos; //converts position 
        return 1; //converted to still ball
        
    } 

    return 0; //ball not converted to still
}

void phylib_bounce( phylib_object **a, phylib_object **b){
    //can assume object a is ALWAYS a rolling ball

    //printf("inside bounce fn");
    if( a == NULL || *a == NULL){ //check if NULL
        return; //do nothing
    }

        if( b == NULL || *b == NULL){ //check if NULL
        return; //do nothing
    }
    
    //bounce is based on what b is
    switch ((*b)->type){
        case PHYLIB_HCUSHION:
            //reverse sign of vel and acc in y direction
            (*a)->obj.rolling_ball.vel.y = -(*a)->obj.rolling_ball.vel.y;
            (*a)->obj.rolling_ball.acc.y = -(*a)->obj.rolling_ball.acc.y;
            break;

        case PHYLIB_VCUSHION:
            //reverse sign of vel and acc in x direction
            (*a)->obj.rolling_ball.vel.x = -(*a)->obj.rolling_ball.vel.x;
            (*a)->obj.rolling_ball.acc.x = -(*a)->obj.rolling_ball.acc.x;
            break;

        case PHYLIB_HOLE:
            //free a and set to NULL
            //printf("freeing object a\n");
            free(*a);
            (*a) = NULL;
            break;
        
        case PHYLIB_STILL_BALL: 
            //'upgrade' to a rolling ball 
            (*b)->type = PHYLIB_ROLLING_BALL;
            (*b)->obj.rolling_ball.vel = (phylib_coord){0, 0}; //set vels to (0, 0)
            (*b)->obj.rolling_ball.acc = (phylib_coord){0, 0}; //set accs to (0, 0)
            //auto moves to next case
        case PHYLIB_ROLLING_BALL:
        ;
            //calculate position of a wrt b
            phylib_coord r_ab = phylib_sub((*a)->obj.rolling_ball.pos, (*b)->obj.rolling_ball.pos); //phylib_sub will find difference

            //calculate relative vel of a wrt b
            phylib_coord v_rel = phylib_sub((*a)->obj.rolling_ball.vel, (*b)->obj.rolling_ball.vel); //phylib_sub will find difference

            //calculate normal vector
            //divide x and y of r_ab by length of r_ab
            phylib_coord n = {(r_ab.x / phylib_length(r_ab)), (r_ab.y / phylib_length(r_ab))};

            //calculate the ratio of the relative velocity by dot product
            double v_rel_n = phylib_dot_product(v_rel, n); //fn will calculate dot product

            //update the x and y velocities of a
            //velocity = velocity - v_rel_n*n.x
            (*a)->obj.rolling_ball.vel.x -= v_rel_n * n.x;
            (*a)->obj.rolling_ball.vel.y -= v_rel_n * n.y;

            //update the x and y velocities of b
            //velocity = velocity + v_rel_n*n.x
            (*b)->obj.rolling_ball.vel.x += v_rel_n * n.x;
            (*b)->obj.rolling_ball.vel.y += v_rel_n * n.y;

            //compute speeds of a & b -> length of its velocity
            double aSpeed = phylib_length((*a)->obj.rolling_ball.vel);
            double bSpeed = phylib_length((*b)->obj.rolling_ball.vel);

            //check if a's speed is GREATER THAN epsilon
            //if true acc = (-vel/speed)*DRAG
            if (aSpeed > PHYLIB_VEL_EPSILON){
                (*a)->obj.rolling_ball.acc.x = -(*a)->obj.rolling_ball.vel.x / aSpeed * PHYLIB_DRAG;
                (*a)->obj.rolling_ball.acc.y = -(*a)->obj.rolling_ball.vel.y / aSpeed * PHYLIB_DRAG;
            } else {
                (*a)->obj.rolling_ball.acc = (phylib_coord){0, 0};
            }
            
            //check if b's speed is GREATER THAN epsilon
            //if true acc = (-vel/speed)*DRAG
            if (bSpeed > PHYLIB_VEL_EPSILON){
                (*b)->obj.rolling_ball.acc.x = -(*b)->obj.rolling_ball.vel.x / bSpeed * PHYLIB_DRAG;
                (*b)->obj.rolling_ball.acc.y = -(*b)->obj.rolling_ball.vel.y / bSpeed * PHYLIB_DRAG;
            } else {
                (*b)->obj.rolling_ball.acc = (phylib_coord){0, 0};
            }
            break;

        default:
        //do nothing case
        break;
            
    }
}

unsigned char phylib_rolling( phylib_table *t){
    if( t == NULL){ //check if NULL
        return 0; //0 if NULL
    }

    unsigned char numRolling = 0; //counter

    //iterate through object array elements
    for (int i = 0; i < PHYLIB_MAX_OBJECTS; i++){
        //checks if obj exists and is of type rolling_ball
        if (t->object[i] != NULL && t->object[i]->type == PHYLIB_ROLLING_BALL){
             numRolling++; //adds one to number of rolling_balls
        }
    }

    return numRolling;
}

phylib_table *phylib_segment(phylib_table *table) {
    //printf("Starting to segment fn\n");
    if (table == NULL || phylib_rolling(table) == 0) { //checks if NULL or no rolling balls
        return NULL;
    }

    //create a copy of table
    phylib_table *copiedTable = phylib_copy_table(table);

    //check to make sure table copied
    if (copiedTable == NULL) { //checks if NULL
        //printf("table didnt copy properly\n");
        return NULL;
    }

    //checks to make sure balls are rolling
    if( phylib_rolling(copiedTable) == 0){ //balls are rolling
        return NULL;   
    }

    //flags
    int rolling = 1; //obj is rolling ball

    //printf("Starting while loop\n");
    //while loop till max time is reached
    while (copiedTable->time < PHYLIB_MAX_TIME && rolling == 1) {
        //printf("time = %6.1lf;\n", copiedTable->time);  // Add this line for debugging

        //iterate through object array elements
        for (int i = 0; i < PHYLIB_MAX_OBJECTS; i++) {
            if (copiedTable->object[i] != NULL && copiedTable->object[i]->type == PHYLIB_ROLLING_BALL) {
                rolling = 1;
                phylib_object *current = copiedTable->object[i];
                phylib_object temp = *current;
            
                //make roll with current time
                //printf("roll fn starting\n");
                phylib_roll(&temp, current, PHYLIB_SIM_RATE);

                //check for collisions
                for (int j = 0; j < PHYLIB_MAX_OBJECTS; j++) { //iterate through again to compare two objs
                    if (copiedTable->object[j] != NULL && i != j) { //checks if same obj is being compared and both are not NULL
                        //calculate distance between two objects
                        double distance = phylib_distance(&temp, copiedTable->object[j]);
                        //printf("distance = %f", distance);

                        if (distance <= 0.0) {
                            //apply bounce and update table
                            //printf("starting bounce fn inside segement fn\n");
                            phylib_bounce(&(copiedTable->object[i]), &(copiedTable->object[j]));
                            return copiedTable;
                        }
                    }  
                }
                //if rolling balls have stopped
                if (phylib_stopped(&temp) == 0){
                    *current = temp; //set current to temp obj
                } else{
                    rolling = 0; // no rolling balls
                }
            }
        }
        
        copiedTable->time += PHYLIB_SIM_RATE; //update time in table       
    }

    return copiedTable;
}


