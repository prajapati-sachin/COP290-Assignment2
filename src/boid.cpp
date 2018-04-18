#include "../include/boid.h"

using namespace std;



Boid::Boid();

void Boid::findneighbours(vector<Boid> all){
	vector<Boid> temp_neighbours;
	for(int i=0; i< all.size(); i++){
		Boid temp = all.get(i);
		if (temp != this){
			if(Distance(temp,this)<=RADIUS){
				temp_neighbours.pushback(temp);
			}
		}
	}
	neighbours = temp_neighbours;
}

Direction Boid::get_average_direction_Alignment(){
	Direction temp_direction;
	float sum_i,sum_j,sum_k = 0;
	float count;
	for(int i=0;i<neighbours.size();i++){
		Boid temp = (neighbours.get(i)).direction;
		if(Distance(temp,this)<=Align_Radius){
			sum_i = sum_i + temp.i;
			sum_j = sum_j + temp.j;
			sum_k = sum_k + temp.k;
			count++;
		}
	}
	temp_direction.i = sum_i/count;
	temp_direction.j = sum_j/count;
	temp_direction.k = sum_k/count;

	return temp_direction;

}

Position Boid::get_average_location_Cohesion(){
	Position temp_position;
	float sum_x,sum_y,sum_z = 0;
	float count;
	for(int i=0;i<neighbours.size();i++){
		Position temp = (neighbours.get(i)).location;
		if(Distance(temp,this)<=Cohese_Radius){
			sum_x = sum_x + temp.x;
			sum_y = sum_y + temp.y;
			sum_z = sum_z + temp.z;
			count++;
		}
	}
	temp_position.x = sum_x/count;
	temp_position.y = sum_y/count;
	temp_position.z = sum_z/count;

	return temp_position;

}

Position Boid::get_average_location_seperation(){
	Position temp_position;
	float sum_x,sum_y,sum_z = 0;
	float count;
	for(int i=0;i<neighbours.size();i++){
		Position temp = (neighbours.get(i)).location;
		if(Distance(temp,this)<=Seperation_Radius){
			sum_x = sum_x + temp.x;
			sum_y = sum_y + temp.y;
			sum_z = sum_z + temp.z;
			count++;
		}
	}
	temp_position.x = sum_x/count;
	temp_position.y = sum_y/count;
	temp_position.z = sum_z/count;

	return temp_position;

}








float distance_between_boids(Boid boid1,Boid boid2){
	float x2 = (boid1.x - boid2.x)*(boid1.x - boid2.x);
	float y2 = (boid1.y - boid2.y)*(boid1.y - boid2.y);
	float z2 = (boid1.z - boid2.z)*(boid1.z - boid2.z);
	float result = x2+y2+z2;
	return sqrt(result);
}

