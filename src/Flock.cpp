#include "../include/Flock.h"

using namespace std;

Flock::Flock();

void Flock::addBoid(Position p){
	Boid B = Boid(p,speed,Boids,Obstacles);
	for(int i=0;i<Boids.size();i++){
		(Boids.get(i)).neighbours.push_back(B)
	}
	Boids.push_back(B);
}

