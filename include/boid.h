#ifndef BOID
#define BOID

#include <vector>
#include "math."

extern float RADIUS;
extern float Align_Radius;
extern float Cohese_Radius;
extern float Seperation_Radius;

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

	Boid():

	void findneighbours(vector<Boid> all);

	Direction get_average_direction();

	Position get_average_location();
}


float distance_boids(Boid boid1,Boid boid2);