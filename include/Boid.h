#ifndef BOID
#define BOID

#include <vector>
#include "math.h"

extern float Align_Radius;
extern float Cohese_Radius;
extern float Seperation_Radius;
extern float Obstacle_radius;
extern float Alignment_parameter;
extern float Cohesion_parameter;
extern float Seperation_parameter;
extern float Obstacle_parameter;



struct Position{
	float x; //x-coordinate
	float y; //y-coordinate
	float z; //z-coordinate
}

struct Direction{
	float i; //i-direction
	float j; //j-direction
	float k; //k-direction
}

class Boid{
	public:

	Position location;

	Direction direction;

	float speed;

	vector<Boid> neighbours;

	vevtor<Obstacle> obstacles;

	Boid():

	Boid(Position p,float speed,vector<Boid> neighbours,vector<Obstacle> obstacles);

	// void findneighbours(vector<Boid> all);

	Direction Boid::Direction_due_to_Alignment();

	Direction Boid::Direction_due_to_Cohesion();

	Direction Boid::Direction_due_to_seperation();

	Direction Boid::Direction_due_to_Obstacle();

	Direction Boid::next_Direction();

	


}

class Obstacle{
	public:

	Position location; 
}

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