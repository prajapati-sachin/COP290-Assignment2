#include "../include/Boid.h"

using namespace std;



Boid::Boid();

Boid::Boid(Position p,float speed,vector<Boid> neighbours,vector<Obstacle> obstacles){
	Direction d;
	this->location = p;
	this->speed = speed;
	this->direction = d;
	this->neighbours = neighbours;
	this->obstacles = obstacles;
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

Direction Boid::get_average_direction_Alignment(){
	Direction temp_direction;
	float sum_i,sum_j,sum_k = 0;
	float count;
	for(int i=0;i<neighbours.size();i++){
		Boid temp = (neighbours.get(i)).direction;
		if(Distance(temp,(this->direction))<=Align_Radius){
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

Direction Boid::Direction_due_to_Cohesion(){
	Position temp_position;
	float sum_x,sum_y,sum_z = 0;
	float count;
	for(int i=0;i<neighbours.size();i++){
		Position temp = (neighbours.get(i)).location;
		if(Distance(temp,(this->location))<=Cohese_Radius){
			sum_x = sum_x + temp.x;
			sum_y = sum_y + temp.y;
			sum_z = sum_z + temp.z;
			count++;
		}
	}
	temp_position.x = sum_x/count;
	temp_position.y = sum_y/count;
	temp_position.z = sum_z/count;

	Direction temp_direction = direction_between_two_locations(temp_position,this->location) ;
	return temp_direction;

}

Direction Boid::Direction_due_to_seperation(){
	Position temp_position;
	float sum_x,sum_y,sum_z = 0;
	float count;
	for(int i=0;i<neighbours.size();i++){
		Position temp = (neighbours.get(i)).location;
		if(Distance(temp,(this->location))<=Seperation_Radius){
			sum_x = sum_x + temp.x;
			sum_y = sum_y + temp.y;
			sum_z = sum_z + temp.z;
			count++;
		}
	}
	temp_position.x = sum_x/count;
	temp_position.y = sum_y/count;
	temp_position.z = sum_z/count;

	Direction temp_direction = direction_between_two_locations(temp_position,this->location) ;
	return temp_direction;
}

Direction Boid::Direction_due_to_Obstacle(){
	Position temp_position;
	float sum_x,sum_y,sum_z = 0;
	float count;
	for(int i=0;i<obstacles.size();i++){
		Position temp = (obstacles.get(i)).location;
		if(Distance(temp,(this->location))<=Obstacle_Radius){
			sum_x = sum_x + temp.x;
			sum_y = sum_y + temp.y;
			sum_z = sum_z + temp.z;
			count++;
		}
	}
	temp_position.x = sum_x/count;
	temp_position.y = sum_y/count;
	temp_position.z = sum_z/count;

	Direction temp_direction = direction_between_two_locations(temp_position,this->location) ;
	return temp_direction;
}

Direction Boid::next_Direction(){
	Direction d1 = Direction_due_to_Alignment();
	Direction d2 = Direction_due_to_Cohesion();
	Direction d3 = Direction_due_to_seperation();
	Direction d4 = Direction_due_to_Obstacle();

	Direction d;
	d.i = (d1.i*Alignment_parameter + d2.i*Cohesion_parameter + d3.i*Seperation_parameter + d4.i*Obstacle_parameter)/400.0;
	d.j = (d1.j*Alignment_parameter + d2.j*Cohesion_parameter + d3.j*Seperation_parameter + d4.j*Obstacle_parameter)/400.0;
	d.k = (d1.k*Alignment_parameter + d2.k*Cohesion_parameter + d3.k*Seperation_parameter + d4.k*Obstacle_parameter)/400.0;
    return d;

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

