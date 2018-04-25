#ifndef FLOCK
#define FLOCK

#include <vector>
#include "math.h"
#include "boid.h"

class flock
{
public:
	
	vector<Boid> Boids;

	vector<Obstacle> Obstacles;

	float speed;

	Flock();

	void addBoid(Position p);

	void removeBoid(Position p);
	
};

