#include "../include/Boid.h"
#include <iostream>
using namespace std;



Boid::Boid(){};

Boid::Boid(Position p, Direction d, vector<Obstacle> obstacles){
	this->location = p;
	this->direction = d;
	this->obstacles = obstacles;
	this->xlimit_max = 0;
	this->ylimit_max = 0;
	this->zlimit_max = 0;
	this->xlimit_min = 0;
	this->ylimit_min = 0;
	this->zlimit_min = 0;


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
	float count=0;
	for(int i=0;i<neighbours.size();i++){
		if(distance_between_positions((neighbours[i])->location,(this->location))<=Align_Radius && distance_between_positions((neighbours[i])->location,(this->location))>0){
			temp_direction = temp_direction + neighbours[i]->direction;
			count++;
		}
	}
	if(count !=0){
		temp_direction = temp_direction/count;
	}

	// cout << temp_direction.i << "|" << temp_direction.j << "|" << temp_direction.k<< "\n";
	return temp_direction;

}

Direction Boid::Direction_due_to_Cohesion(){
	Position temp_position;
	int flag=0;
	float count=0;
	for(int i=0;i<neighbours.size();i++){
		if(distance_between_positions((neighbours[i]->location),(this->location))<=Cohese_Radius && distance_between_positions((neighbours[i]->location),(this->location))>0){
			temp_position = temp_position + (neighbours[i]->location);
			count++;
			flag=1;
		}
	}
	if(count !=0){
		temp_position = temp_position/count;
	}

	Direction temp_direction;
	if(flag==1){
		temp_direction = direction_between_two_locations(temp_position,this->location);		
	}
	return temp_direction;
}

Direction Boid::Direction_due_to_seperation(){
	Position temp_position;
	int flag=0;
	float sum_x=0;
	float sum_y=0;
	float sum_z=0;
	float count=0;
	for(int i=0;i<neighbours.size();i++){
		if(distance_between_positions((neighbours[i]->location),(this->location))<=Seperation_Radius && distance_between_positions((neighbours[i]->location),(this->location))>0){
			temp_position = temp_position + neighbours[i]->location;
			count++;
			flag=1;
		}
	}
	if(count !=0){
		temp_position = temp_position/count;
	}

	Direction temp_direction;
	if(flag==1){
		temp_direction = direction_between_two_locations(temp_position,this->location);		
	}
	return temp_direction;
}

Direction Boid::Direction_due_to_Obstacle(){
	Position temp_position;
	int flag =0;
	float sum_x=0;
	float sum_y=0;
	float sum_z=0;
	float count=0;
	for(int i=0;i<obstacles.size();i++){
		if(distance_between_positions((obstacles[i].location),(this->location))<=Obstacle_Radius && distance_between_positions((obstacles[i].location),(this->location))>0){
			temp_position = temp_position + (obstacles[i].location);
			count++;
			flag=1;
		}
	}
	if(count !=0){
		temp_position = temp_position/count;
	}
	Direction temp_direction;
	if(flag==1){
		temp_direction = direction_between_two_locations(temp_position,this->location);		
	}
	return temp_direction;
}

Direction Boid::next_Direction(){
	Direction d1 = Direction_due_to_Alignment();
	Direction d2 = Direction_due_to_Cohesion();
	Direction d3 = Direction_due_to_seperation();
	Direction d4 = Direction_due_to_Obstacle();

	// cout << xlimit << "|"<< ylimit << "|"<< zlimit << "\n";
	// cout << direction.i << "|" << direction.j << "|" << direction.k << "\n";
	Direction temp_d;
	if(xlimit_max==1){
		temp_d.i = ((Inertia_parameter*direction.i)  + (Limit_parameter*(0.1))+ (d1.i*Alignment_parameter + d2.i*Cohesion_parameter + d3.i*Seperation_parameter + d4.i*Obstacle_parameter));
	}else if(xlimit_min==1){
		temp_d.i = ((Inertia_parameter*direction.i)  + (Limit_parameter*(-0.1))+ (d1.i*Alignment_parameter + d2.i*Cohesion_parameter + d3.i*Seperation_parameter + d4.i*Obstacle_parameter));
	}
	else{
		temp_d.i = ((Inertia_parameter*direction.i)  +  (d1.i*Alignment_parameter + d2.i*Cohesion_parameter + d3.i*Seperation_parameter + d4.i*Obstacle_parameter));
	}
	if(ylimit_max==1){
		temp_d.j = ((Inertia_parameter*direction.j)  + (Limit_parameter*(0.1))+ (d1.j*Alignment_parameter + d2.j*Cohesion_parameter + d3.j*Seperation_parameter + d4.j*Obstacle_parameter));
	}else if(ylimit_min==1){
		temp_d.j = ((Inertia_parameter*direction.j)  + (Limit_parameter*(-0.1))+ (d1.j*Alignment_parameter + d2.j*Cohesion_parameter + d3.j*Seperation_parameter + d4.j*Obstacle_parameter));
	}
	else{
		temp_d.j = ((Inertia_parameter*direction.j)  +  (d1.j*Alignment_parameter + d2.j*Cohesion_parameter + d3.j*Seperation_parameter + d4.j*Obstacle_parameter));
	}
	if(zlimit_max==1){
		temp_d.k = ((Inertia_parameter*direction.k)  + (Limit_parameter*(0.1))+ (d1.k*Alignment_parameter + d2.k*Cohesion_parameter + d3.k*Seperation_parameter + d4.k*Obstacle_parameter));
    }else if(zlimit_min==1){
    	temp_d.k = ((Inertia_parameter*direction.k)  + (Limit_parameter*(-0.1))+ (d1.k*Alignment_parameter + d2.k*Cohesion_parameter + d3.k*Seperation_parameter + d4.k*Obstacle_parameter));
    }
    else{
    	temp_d.k = ((Inertia_parameter*direction.k)  + (Limit_parameter*(-0.1))+ (d1.k*Alignment_parameter + d2.k*Cohesion_parameter + d3.k*Seperation_parameter + d4.k*Obstacle_parameter));
    }
    // Direction d_unit = generate_unit_vector(temp_d);
    return temp_d;
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
	d_unit.i= i/mag;
	d_unit.j= j/mag;
	d_unit.k= k/mag;
	return d_unit;
}