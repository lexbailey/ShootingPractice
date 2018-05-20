/*! \file constraints.h
    \brief Defines constraints
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This is used by the physics library for constraining objects

    (University of York C Programming Labs assessment)
*/

#ifndef CONSTRAINTS_INCLUDE
#define CONSTRAINTS_INCLUDE

///Enumerated type marking constratints as minimums or maximums
typedef enum {ct_MinTranslation, ct_MaxTranslation} constraintType;

///A constraint for a physics object
typedef struct {
	float value;
	axis_t axis;
	constraintType type;
}
constraint_t;

#endif //CONSTRAINTS_INCLUDE
