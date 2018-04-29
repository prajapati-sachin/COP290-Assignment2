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
	// cout << temp_direction.i << "|" << temp_direction.j << "|" << temp_direction.k<< "\n";

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
		temp_direction = direction_between_two_locations(this->location, temp_position);		
	}
	// cout << temp_direction.i << "|" << temp_direction.j << "|" << temp_direction.k<< "\n";

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
	// cout << temp_direction.i << "|" << temp_direction.j << "|" << temp_direction.k<< "\n";

	return temp_direction;
}

Direction Boid::next_Direction(){
	Direction d1 = Direction_due_to_Alignment();
	Direction d2 = Direction_due_to_Cohesion();
	Direction d3 = Direction_due_to_seperation();
	Direction d4 = Direction_due_to_Obstacle();

	// cout << d1.i << "|" << d1.j << "|" << d1.k << "\n";

	// cout << d1.i << "|" << d2.j << "|" << d3.k << "\n";


	// cout << xlimit << "|"<< ylimit << "|"<< zlimit << "\n";
	// cout << direction.i << "|" << direction.j << "|" << direction.k << "\n";
	Direction temp_d;
	if(xlimit_max==1){
		temp_d.i = ((Inertia_parameter*direction.i)  + (Limit_parameter*(0.1))+ 0.3*((d1.i*Alignment_parameter + d2.i*Cohesion_parameter + d3.i*Seperation_parameter + d4.i*Obstacle_parameter)-direction.i));
	}else if(xlimit_min==1){
		temp_d.i = ((Inertia_parameter*direction.i)  + (Limit_parameter*(-0.1))+ 0.3*((d1.i*Alignment_parameter + d2.i*Cohesion_parameter + d3.i*Seperation_parameter + d4.i*Obstacle_parameter)-direction.i));
	}
	else{
		temp_d.i = ((Inertia_parameter*direction.i)  +  0.3*((d1.i*Alignment_parameter + d2.i*Cohesion_parameter + d3.i*Seperation_parameter + d4.i*Obstacle_parameter) - direction.i));
	}
	if(ylimit_max==1){
		temp_d.j = ((Inertia_parameter*direction.j)  + (Limit_parameter*(0.1))+ 0.3*((d1.j*Alignment_parameter + d2.j*Cohesion_parameter + d3.j*Seperation_parameter + d4.j*Obstacle_parameter) - direction.j));
	}else if(ylimit_min==1){
		temp_d.j = ((Inertia_parameter*direction.j)  + (Limit_parameter*(-0.1))+ 0.3*((d1.j*Alignment_parameter + d2.j*Cohesion_parameter + d3.j*Seperation_parameter + d4.j*Obstacle_parameter) -direction.j));
	}
	else{
		temp_d.j = ((Inertia_parameter*direction.j)  +  0.3*((d1.j*Alignment_parameter + d2.j*Cohesion_parameter + d3.j*Seperation_parameter + d4.j*Obstacle_parameter)-direction.j));
	}
	if(zlimit_max==1){
		temp_d.k = ((Inertia_parameter*direction.k)  + (Limit_parameter*(0.1))+ 0.3*((d1.k*Alignment_parameter + d2.k*Cohesion_parameter + d3.k*Seperation_parameter + d4.k*Obstacle_parameter)-direction.k));
    }else if(zlimit_min==1){
    	temp_d.k = ((Inertia_parameter*direction.k)  + (Limit_parameter*(-0.1))+ 0.3*((d1.k*Alignment_parameter + d2.k*Cohesion_parameter + d3.k*Seperation_parameter + d4.k*Obstacle_parameter)-direction.k));
    }
    else{
    	temp_d.k = ((Inertia_parameter*direction.k)  + 0.3*((d1.k*Alignment_parameter + d2.k*Cohesion_parameter + d3.k*Seperation_parameter + d4.k*Obstacle_parameter)-direction.k));
    }
    


    Direction d_unit;
    if(magnitude(temp_d) > 5){
    	// d_unit = generate_unit_vector(temp_d);
   		d_unit.i = (temp_d.i*5)/magnitude(temp_d);
   		d_unit.j = (temp_d.j*5)/magnitude(temp_d);
   		d_unit.k = (temp_d.k*5)/magnitude(temp_d);
    
    }else if(magnitude(temp_d) < 0.1){
    	d_unit.i = (temp_d.i*0.1)/magnitude(temp_d);
   		d_unit.j = (temp_d.j*0.1)/magnitude(temp_d);
   		d_unit.k = (temp_d.k*0.1)/magnitude(temp_d);
	}else{d_unit=temp_d;}

	// cout << d_unit.i << "|" << d_unit.j << "|" << d_unit.k << "\n";
    
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
	d.i = p1.x - p2.x;
	d.j = p1.y - p2.y;
	d.k = p1.z - p2.z;
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

float magnitude(Direction d){
	float i = d.i;
	float j = d.j;
	float k = d.k;
	float mag = sqrt((i*i) + (j*j) + (k*k));
	return mag;
}