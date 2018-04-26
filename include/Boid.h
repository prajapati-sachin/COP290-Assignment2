#ifndef BOID
#define BOID

#include <vector>
#include "math.h"

using namespace std;
///////////////////

#define speed 0.1
#define Align_Radius 1
#define Cohese_Radius 1
#define Seperation_Radius 1
#define Obstacle_Radius 1
#define Inertia_parameter 1
#define Alignment_parameter 0.25
#define Cohesion_parameter 0.25
#define Seperation_parameter 0.25
#define Obstacle_parameter 0.01
#define Limit_parameter -5
#define xmax  10
#define ymax  20
#define zmax  10
#define xmin  -10
#define ymin  5
#define zmin  -10

////////////////////

struct Position{
	float x; //x-coordinate
	float y; //y-coordinate
	float z; //z-coordinate
};

struct Direction{
	float i; //i-direction
	float j; //j-direction
	float k; //k-direction
};

class Obstacle{
	public:

	Position location; 
};


class Boid{
	public:

	Position location;

	Direction direction;

	vector<Boid> neighbours;

	vector<Obstacle> obstacles;

	int xlimit, ylimit, zlimit;

	Boid();

	Boid(Position p, Direction d, vector<Boid> neighbours,vector<Obstacle> obstacles);

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

#endif