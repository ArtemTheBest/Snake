#include "Field.h"

#include <glut.h>

size_t Field::get_size_x()const{
	return this->size_x;
}

size_t Field::get_size_y()const{
	return this->size_y;
}

size_t Field::get_width()const{
	return this->width;
}

size_t Field::get_height()const{
	return this->height;
}

void Field::set_width(size_t width){
	this->width = width;
}

void Field::set_height(size_t height){
	this->height = height;
}

void Field::draw()const{
	glColor3f(0.627, 0.878, 0.501);

	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(0, this->height, 0);
		glVertex3f(this->width, this->height, 0);
		glVertex3f(this->width, 0, 0);
	glEnd();
}