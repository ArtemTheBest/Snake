#include "Menu.h"

#include <string>
#include <glut.h>

Menu *Menu::static_this;

void Menu::draw_a_separate_screen()const{
	glClear(GL_COLOR_BUFFER_BIT);
	


	glutSwapBuffers();
}

void Menu::move_down(){
	this->cur_position = (this->cur_position + 1) % this->arr.size();
}

void Menu::move_up(){
	this->cur_position = this->cur_position == 0 ? this->arr.size() - 1 : 
		this->cur_position - 1;
}

size_t Menu::get_cur_position()const{
	return cur_position + 1;
}

void Menu::draw_string(std::string str, int x_coordinate, int y_coordinate)const{
	const char *text = str.c_str();
	glRasterPos2d(x_coordinate,y_coordinate);

	while (*text) 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text++);
}