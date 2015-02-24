#include "GoodItem.h"

#include <glut.h>

Effect GoodItem::get_effect()const{
	return good;
}

Point GoodItem::get_position()const{
	return this->position;
}

void GoodItem::draw()const{
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glVertex3f(this->position.x, this->position.y, 0);
		glVertex3f(this->position.x + 1, this->position.y, 0);
		glVertex3f(this->position.x + 1, this->position.y + 1, 0);
		glVertex3f(this->position.x, this->position.y +1, 0);
	glEnd();
	
	glColor3f(0.2,0.8,0.2);
	glBegin(GL_QUADS);
		glVertex3f(this->position.x + 0.1, this->position.y + 0.1, 0);
		glVertex3f(this->position.x + 0.9, this->position.y + 0.1, 0);
		glVertex3f(this->position.x + 0.9, this->position.y + 0.9, 0);
		glVertex3f(this->position.x + 0.1, this->position.y + 0.9, 0);
	glEnd();
}
