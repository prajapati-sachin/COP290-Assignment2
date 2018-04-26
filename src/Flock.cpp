#include "../include/Flock.h"
#include <iostream>
using namespace std;

Flock::Flock(){};

void Flock::addBoid(Position p){
	Direction d;
	d.i=1;
	d.j=1;
	d.k=1;
	Direction dr = generate_unit_vector(d);
	Boid B = Boid(p, dr, Boids, Obstacles);
	for(int i=0;i<Boids.size();i++){
		(Boids[i]).neighbours.push_back(B);
	}
	Boids.push_back(B);
}

void Flock::update_positions(vector<Position> p){
	for(int i=0;i<Boids.size();i++){
		if(p[i].x> xmax || p[i].x< xmin){
			Boids[i].xlimit=1;
			cout << "bahar pahunh gya\n";
		} else{
			Boids[i].xlimit=0;
			cout << "andar hi hun\n";
		}
		if(p[i].y> ymax || p[i].y< ymin){
			Boids[i].ylimit=1;
			cout << "bahar pahunh gya\n";
		}else{
			Boids[i].ylimit=0;
			cout << "andar hi hun\n";
		}
		if(p[i].z> zmax || p[i].z< zmin){
			Boids[i].zlimit=1;
			cout << "bahar pahunh gya\n";
		} else{
			Boids[i].zlimit=0;
			cout << "andar hi hun\n";
		}			
		Boids[i].location = p[i];
		cout << "\n";
	}

}

void Flock::update_directions(){
	for(int i=0;i<Boids.size();i++){
		Boids[i].direction = Boids[i].next_Direction();
	}

}