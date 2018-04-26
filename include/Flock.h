#ifndef FLOCK
#define FLOCK

#include <vector>
#include "math.h"
#include "Boid.h"

class Flock
{
public:
	
	vector<Boid> Boids;

	vector<Obstacle> Obstacles;

	Flock();

	void addBoid(Position p);

	void removeBoid(Position p);
		
	void update_positions(vector<Position> p);

	void update_directions();

};

#endif
