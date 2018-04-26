#include "../include/Boid.h"
#include <iostream>
using namespace std;



Boid::Boid(){};

Boid::Boid(Position p, Direction d, vector<Boid> neighbours,vector<Obstacle> obstacles){
	this->location = p;
	this->direction = d;
	this->neighbours = neighbours;
	this->obstacles = obstacles;
	this->xlimit = 0;
	this->ylimit = 0;
	this->zlimit = 0;

}
// void Boid::findneighbours(vector<Boid> all){
// 	vector<Boid> temp_neighbours;
// 	for(int i=0; i< all.size(); i++){
// 		Boid temp = all.get(i);
// 		if (temp != this){
// 			if(Distance(temp,this)<=RADIUS){
// 				temp_neighbours.pushback(temp);
// 			}
// 		}
// 	}
// 	neighbours = temp_neighbours;
// }

Direction Boid::Direction_due_to_Alignment(){
	Direction temp_direction;
	float sum_i=0;
	float sum_j=0;
	float sum_k=0;
	float count=0;
	for(int i=0;i<neighbours.size();i++){
		Boid temp = (neighbours[i]);
		if(distance_between_positions(temp.location,(this->location))<=Align_Radius && distance_between_positions(temp.location,(this->location))>0){
			sum_i = sum_i + (temp.direction).i;
			sum_j = sum_j + (temp.direction).j;
			sum_k = sum_k + (temp.direction).k;
			count++;
		}
	}
	if(count !=0){
		temp_direction.i = sum_i/count;
		temp_direction.j = sum_j/count;
		temp_direction.k = sum_k/count;
	}
	else{
		temp_direction.i = sum_i;
		temp_direction.j = sum_j;
		temp_direction.k = sum_k;
	}
	// cout << "mere to lo lag gye";
	// cout << temp_direction.i << "|" << temp_direction.j << "|" << temp_direction.k<< "\n";
	return temp_direction;

}

Direction Boid::Direction_due_to_Cohesion(){
	Position temp_position;
	float sum_x=0;
	float sum_y=0;
	float sum_z=0;
	float count=0;
	for(int i=0;i<neighbours.size();i++){
		Position temp = (neighbours[i].location);
		if(distance_between_positions(temp,(this->location))<=Cohese_Radius && distance_between_positions(temp,(this->location))>0){
			sum_x = sum_x + temp.x;
			sum_y = sum_y + temp.y;
			sum_z = sum_z + temp.z;
			count++;
		}
	}
	if(count !=0){
		temp_position.x = sum_x/count;
		temp_position.y = sum_y/count;
		temp_position.z = sum_z/count;
	}
	else{
		temp_position.x = sum_x;
		temp_position.y = sum_y;
		temp_position.z = sum_z;
	}
	
	Direction temp_direction = direction_between_two_locations(temp_position,this->location) ;
	return temp_direction;

}

Direction Boid::Direction_due_to_seperation(){
	Position temp_position;
	float sum_x=0;
	float sum_y=0;
	float sum_z=0;
	float count=0;
	for(int i=0;i<neighbours.size();i++){
		Position temp = (neighbours[i].location);
		if(distance_between_positions(temp,(this->location))<=Seperation_Radius && distance_between_positions(temp,(this->location))>0){
			sum_x = sum_x + temp.x;
			sum_y = sum_y + temp.y;
			sum_z = sum_z + temp.z;
			count++;
		}
	}
	if(count !=0){
		temp_position.x = sum_x/count;
		temp_position.y = sum_y/count;
		temp_position.z = sum_z/count;
	}
	else{
		temp_position.x = sum_x;
		temp_position.y = sum_y;
		temp_position.z = sum_z;
	}
	
	Direction temp_direction = direction_between_two_locations(temp_position,this->location) ;
	return temp_direction;
}

Direction Boid::Direction_due_to_Obstacle(){
	Position temp_position;
	float sum_x=0;
	float sum_y=0;
	float sum_z=0;
	float count=0;
	for(int i=0;i<obstacles.size();i++){
		Position temp = (obstacles[i]).location;
		if(distance_between_positions(temp,(this->location))<=Obstacle_Radius && distance_between_positions(temp,(this->location))>0){
			sum_x = sum_x + temp.x;
			sum_y = sum_y + temp.y;
			sum_z = sum_z + temp.z;
			count++;
		}
	}
	if(count !=0){
		temp_position.x = sum_x/count;
		temp_position.y = sum_y/count;
		temp_position.z = sum_z/count;
	}
	else{
		temp_position.x = sum_x;
		temp_position.y = sum_y;
		temp_position.z = sum_z;
	}
	
	Direction temp_direction = direction_between_two_locations(temp_position,this->location) ;
	return temp_direction;
}

Direction Boid::next_Direction(){
	Direction d1 = Direction_due_to_Alignment();
	Direction d2 = Direction_due_to_Cohesion();
	Direction d3 = Direction_due_to_seperation();
	Direction d4 = Direction_due_to_Obstacle();

	Direction temp_d;
	temp_d.i = (Inertia_parameter*direction.i) + (xlimit*(Limit_parameter*direction.i)) + (d1.i*Alignment_parameter + d2.i*Cohesion_parameter + d3.i*Seperation_parameter + d4.i*Obstacle_parameter);
	temp_d.j = (Inertia_parameter*direction.j) + (ylimit*(Limit_parameter*direction.j)) + (d1.j*Alignment_parameter + d2.j*Cohesion_parameter + d3.j*Seperation_parameter + d4.j*Obstacle_parameter);
	temp_d.k = (Inertia_parameter*direction.k) + (zlimit*(Limit_parameter*direction.k)) + (d1.k*Alignment_parameter + d2.k*Cohesion_parameter + d3.k*Seperation_parameter + d4.k*Obstacle_parameter);
    Direction d_unit = generate_unit_vector(temp_d);
    return d_unit;

}


float distance_between_positions(Position p1,Position p2){
	float x2 = (p1.x - p2.x)*(p1.x - p2.x);
	float y2 = (p1.y - p2.y)*(p1.y - p2.y);
	float z2 = (p1.z - p2.z)*(p1.z - p2.z);
	float result = x2+y2+z2;
	return sqrt(result);
}


Direction direction_between_two_locations(Position p1, Position p2){
	Direction d;
	d.i = p2.x - p1.x;
	d.j = p2.y - p1.y;
	d.k = p2.z - p1.z;
	return d;
}



Direction generate_unit_vector(Direction d){
	float i = d.i;
	float j = d.j;
	float k = d.k;
	float mag = sqrt((i*i) + (j*j) + (k*k));
	Direction d_unit;
	if(mag==0){
		cout << "Dikkat he bhaiya";
	}
	d_unit.i= i/mag;
	d_unit.j= j/mag;
	d_unit.k= k/mag;
	return d_unit;
}