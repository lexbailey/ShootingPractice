/*! \file forces.h
    \brief Defines forces
    \author Daniel Bailey
    \copyright Copyright Daniel Bailey 2013 - 2014

    This is used by the physics library

    (University of York C Programming Labs assessment)
*/

#ifndef PHYSICS_FORCES_INCLUDE
#define PHYSICS_FORCES_INCLUDE

///Type of force ft_Static for a constant force, ft_Explosive for a timed impulse
typedef enum {ft_Static, ft_Explosive} forceType;

///Defines a force that can be applied to an object
typedef struct {
	vector3 forceVector;
	forceType type;
	float impulseTime;
} force_t;

#endif //PHYSICS_FORCES_INCLUDE
