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
typedef enum{
    PHYLIB_STILL_BALL = 0,
    PHYLIB_ROLLING_BALL = 1,
    PHYLIB_HOLE = 2,
    PHYLIB_HCUSHION = 3,
    PHYLIB_VCUSHION =4,
} phylib_obj;

//class representing a vector in 2 dimensions
