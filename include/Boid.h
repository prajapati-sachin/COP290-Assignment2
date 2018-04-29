#ifndef BOID
#define BOID

#include <vector>
#include "math.h"

using namespace std;
///////////////////

#define speed 0.1
#define Align_Radius 5
#define Cohese_Radius 5
#define Seperation_Radius 1
#define Obstacle_Radius 1
#define Inertia_parameter 1
#define Alignment_parameter 0.75
#define Cohesion_parameter 0.001
#define Seperation_parameter 0.1	
#define Obstacle_parameter 0
#define Limit_parameter -1
#define xmax  35
#define ymax  40
#define zmax  35
#define xmin  -10
#define ymin  15
#define zmin  -10

////////////////////

struct Position{
	float x; //x-coordinate
	float y; //y-coordinate
	float z; //z-coordinate

	Position(){
		x=y=z=0;
	}
    Position& operator+(const Position& rhs){ 
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    
    Position& operator/(const int c){ 
    x /= c;
    y /= c;
    z /= c;
    return *this;
    }
};

struct Direction{
	float i; //i-direction
	float j; //j-direction
	float k; //k-direction
	Direction(){
		i=j=k=0;
	}
    
    Direction& operator+(const Direction& rhs){ 
        i += rhs.i;
        j += rhs.j;
        k += rhs.k;
        return *this;
    }
    
    Direction& operator/(const int c){ 
    i /= c;
    j /= c;
    k /= c;
    return *this;
    }

};

class Obstacle{
	public:

	Position location; 
};


class Boid{
	public:

	Position location;	

	Direction direction;

	vector<Boid*> neighbours;

	vector<Obstacle> obstacles;

	int xlimit_max, ylimit_max, zlimit_max, xlimit_min, ylimit_min, zlimit_min;

	Boid();

	Boid(Position p, Direction d, vector<Obstacle> obstacles);

	// void findneighbours(vector<Boid> all);

	Direction Direction_due_to_Alignment();

	Direction Direction_due_to_Cohesion();

	Direction Direction_due_to_seperation();

	Direction Direction_due_to_Obstacle();

	Direction next_Direction();
};


//gives distance between two locations
float distance_between_positions(Position p1,Position p2);

//gives direction from one point to other p1->p2
Direction direction_between_two_locations(Position p1, Position p2);

void change_Align_Radius();

void change_Cohese_Radius();

void change_Seperation_Radius();

void change_Obstacle_radius();

void change_Alignment_parameter();

void change_Cohesion_parameter();

void change_Seperation_parameter();

void change_Obstacle_parameter();

Direction generate_unit_vector(Direction d);

float magnitude(Direction d);

#endif