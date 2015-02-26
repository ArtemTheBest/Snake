#include "Snake.h"

#include <glut.h>
#include <GLAux.h>

Point Snake::get_head_position()const{
	return this->blocks_position.front();
}

std::vector<Point> Snake::get_snake()const{
	return this->blocks_position;
}

size_t Snake::length()const{
	return this->blocks_position.size();
}

void Snake::draw()const{
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
		for (size_t i = 0; i < this->blocks_position.size(); i++){
			glVertex3f(this->blocks_position[i].x,this->blocks_position[i].y,0);
			glVertex3f(this->blocks_position[i].x + 1, this->blocks_position[i].y, 0);
			glVertex3f(this->blocks_position[i].x + 1, this->blocks_position[i].y + 1, 0);
			glVertex3f(this->blocks_position[i].x, this->blocks_position[i].y + 1, 0);
		}
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		for (size_t i = 0; i < this->blocks_position.size(); i++){
			glVertex3f(this->blocks_position[i].x + 0.1, this->blocks_position[i].y + 0.1, 0);
			glVertex3f(this->blocks_position[i].x + 0.9, this->blocks_position[i].y + 0.1, 0);
			glVertex3f(this->blocks_position[i].x + 0.9, this->blocks_position[i].y + 0.9, 0);
			glVertex3f(this->blocks_position[i].x + 0.1, this->blocks_position[i].y + 0.9, 0);
		}
	glEnd();
}

void Snake::set_head_position(Point position){
	this->blocks_position[0] = position;
}

void Snake::increase(size_t size){
	for (size_t i = 0; i < size; i++)
		this->blocks_position.push_back(this->blocks_position.back());
}

void Snake::reduce(size_t size){
	if (size >= this->length())
		return;
	
	this->blocks_position.resize(size);
}

void Snake::go_up(){
	if (this->direction != down)
		this->direction = up;
}

void Snake::go_down(){
	if (this->direction != up)
		this->direction = down;
}

void Snake::go_left(){
	if (this->direction != right)
		this->direction = left;
}

void Snake::go_right(){
	if (this->direction != left)
		this->direction = right;
}

void Snake::move(){
	for (size_t i = this->blocks_position.size() - 1; i > 0; i--)
		this->blocks_position[i] = this->blocks_position[i - 1];

	this->blocks_position[0] += get_move_point();
	this->check();
	this->check_on_position();
}

void Snake::check(){
	for (size_t i = 1;i < this->blocks_position.size();i++)
		if (this->get_head_position() == this->blocks_position[i]){
			this->reduce(i);
			return;
		}
}

void  Snake::check_on_position(){
	if (this->get_head_position().x >= this->x_border)
		this->blocks_position[0].x = 0;

	if (this->get_head_position().x < 0)
		this->blocks_position[0].x = this->x_border - 1;

	if (this->get_head_position().y >= this->y_border)
		this->blocks_position[0].y = 0;

	if (this->get_head_position().y < 0)
		this->blocks_position[0].y = this->y_border - 1;
}

Point Snake::get_move_point()const{
	switch (this->direction){
	case up:
		return Point(0,1);
	case down:
		return Point(0,-1);
	case left:
		return Point(-1, 0);
	case right:
		return Point(1, 0);
	default:
		throw std::exception();
	}
}