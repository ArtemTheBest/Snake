#pragma once

#include <vector>

class Menu{
public:
	Menu():cur_position(0),width(800),height(640){}
	Menu(std::vector<std::string> arr) :arr(arr), cur_position(0), width(800), height(640){}

	Menu(std::vector<std::string> arr, int width, int height) :arr(arr), cur_position(0), 
		width(width), height(height){}

	void move_down();
	void move_up();
	
	void draw()const;
	void reshape(int width, int height);
	void timer(int);
	void initialize_gl();
	void special_keyboard(int key, int x, int y);

	size_t get_cur_position()const;

	void set_static_this(Menu *staticThis);
private:
	std::vector<std::string> arr;
	size_t cur_position;
	int width;
	int height;
	
	void draw_string(std::string str, int x_coordinate, int y_coordinate)const;
};