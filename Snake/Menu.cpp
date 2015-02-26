#include "Menu.h"

#include <string>
#include <glut.h>

void Menu::initialize_gl(){
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.627, 0.878, 0.501,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, this->width, 0, this->height, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Menu::special_keyboard(int key, int x, int y){
	switch (key){
	case GLUT_KEY_UP:
		this->move_up();
		break;
	case GLUT_KEY_DOWN:
		this->move_down();
		break;
	}
}

void Menu::draw()const{
	glColor3f(0, 0, 0);

	int y_position = this->height - 40;

	for (auto itr = std::begin(this->arr); itr != std::end(this->arr); itr++,y_position-=30){
		std::string temp = (itr - std::begin(this->arr) == this->cur_position ?
			"> " + *itr + " <" : "  " + *itr + "  ");
		this->draw_string(temp, 20, y_position);
	}
}

void Menu::reshape(int width, int height){
	this->width = width;
	this->height = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, this->width, 0, this->height, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void  Menu::timer(int = 0){
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