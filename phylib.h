// constants

#define PHYLIB_BALL_RADIUS (28.5) //mm
#define PHYLIB_BALL_DIAMETER (2*PHYLIB_BALL_RADIUS)

#define PHYLIB_HOLE_RADIUS (2*PHYLIB_BALL_DIAMETER)
#define PHYLIB_TABLE_LENGTH (2700.0) //mm
#define PHYLIB_TABLE_WIDTH (PHYLIB_TABLE_LENGTH/2.0)

#define PHYLIB_SIM_RATE (0.0001) //s
#define PHYLIB_VEL_EPSILON (0.01) //mm/s

#define PHYLIB_DRAG (150.0) //mm/s^2
#define PHYLIB_MAX_TIME (600) //s

#define PHYLIB_MAX_OBJECTS (26)

//polymorphic obj types defined as enum
//similar to grouped constants
typedef enum {
    PHYLIB_STILL_BALL = 0,
    PHYLIB_ROLLING_BALL = 1,
    PHYLIB_HOLE = 2,
    PHYLIB_HCUSHION = 3,
    PHYLIB_VCUSHION =4,
} phylib_obj;

//class representing a vector in 2 dimensions
typedef struct {
    double x;
    double y;
} phylib_coord;

//Child classes representing objs on the table

//still ball (not in motion)
typedef struct {
    unsigned char number;
    phylib_coord pos;
} phylib_still_ball;

//rolling ball
typedef struct {
    unsigned char number;
    phylib_coord pos;
    phylib_coord vel;
    phylib_coord acc; //negative due to friction
} phylib_rolling_ball;

//hole position
typedef struct {
    phylib_coord pos;
} phylib_hole;

//horizontal cushion position
typedef struct {
    double y; //only has y-coord
} phylib_hcushion;

//vertial cushion position
typedef struct {
    double x; //only has x-coord
} phylib_vcushion;

//polymorphic parent class of objs on the table
typedef union {
    phylib_still_ball still_ball;
    phylib_rolling_ball rolling_ball;
    phylib_hole hole;
    phylib_hcushion hcushion;
    phylib_vcushion vcushion;
} phylib_untyped;

//struct to id what the class of object is
typedef struct {
    phylib_obj type;
    phylib_untyped obj;
} phylib_object;

//table representation
typedef struct {
    double time;
    phylib_object *object[PHYLIB_MAX_OBJECTS];
} phylib_table;