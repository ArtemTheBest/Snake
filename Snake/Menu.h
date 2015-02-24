#pragma once

#include <vector>

class Menu{
public:
	Menu():cur_position(0){}
	Menu(std::vector<std::string> arr) :arr(arr), cur_position(0){}

	void move_down();
	void move_up();

	void draw()const;
	void draw_a_separate_screen()const;

	static void draw_a_separate_screen_call_back();

	size_t get_cur_position()const;
private:
	std::vector<std::string> arr;
	size_t cur_position;

	static Menu *static_this;

	void draw_string(std::string str, int x_coordinate, int y_coordinate)const;
};