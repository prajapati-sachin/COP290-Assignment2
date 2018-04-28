#include "../include/Flock.h"
#include <iostream>
using namespace std;

Flock::Flock(){};

void Flock::addBoid(Position p, Direction d){
	Direction dr = generate_unit_vector(d);
	Boid temp_Boid(p, dr, Obstacles);

	for(int i=0;i<Boids.size();i++){
		// (Boids[i]).neighbours.push_back(&temp_Boid);
		temp_Boid.neighbours.push_back(&Boids[i]);
	}


	for(int i=0;i<Boids.size();i++){
		(Boids[i]).neighbours.push_back(&temp_Boid);
	}
	Boids.push_back(temp_Boid);
}

void Flock::update_positions(vector<Position> p){
	for(int i=0;i<Boids.size();i++){
			
		Boids[i].location = p[i];
		// cout << "\n";
		// SET LIMIT PARAMETERS FOR X COORDINATE
		if(p[i].x > xmax){
			Boids[i].xlimit_max=1;
			Boids[i].xlimit_min=0;
		}else if(p[i].x< xmin){
			Boids[i].xlimit_min=1;
			Boids[i].xlimit_max=0;
		}
		else{
			Boids[i].xlimit_max=0;
			Boids[i].xlimit_min=0;
		}

		// SET LIMIT PARAMETERS FOR Y COORDINATE
		if(p[i].y > ymax){
			Boids[i].ylimit_max=1;
			Boids[i].ylimit_min=0;
		}else if(p[i].y < ymin){
			Boids[i].ylimit_min=1;
			Boids[i].ylimit_max=0;
		}
		else{
			Boids[i].ylimit_max=0;
			Boids[i].ylimit_min=0;
		}


		// SET LIMIT PARAMETERS FOR Z COORDINATE
		if(p[i].z > zmax){
			Boids[i].zlimit_max=1;
			Boids[i].zlimit_min=0;
		}else if(p[i].z< zmin){
			Boids[i].zlimit_min=1;
			Boids[i].zlimit_max=0;
		}
		else{
			Boids[i].zlimit_max=0;
			Boids[i].zlimit_min=0;
		}


	}

}

void Flock::update_directions(){
	for(int i=0;i<Boids.size();i++){
	//	cout << Boids[i].xlimit << "|" << Boids[i].ylimit  << "|" << Boids[i].zlimit << "\n";
		Boids[i].direction = Boids[i].next_Direction();
		// cout << "\n";
	}

}