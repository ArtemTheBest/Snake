#pragma once
#include "Point.h"

#include <vector>

enum Direction{up,down,left,right};

class Snake{
public:
	Snake() : blocks_position(5, Point(0, 0)), direction(up), x_border(0), y_border(0){}
	Snake(size_t size,int x_border,int y_border) : blocks_position(size, Point(0, 0)), 
		direction(up), x_border(x_border), y_border(y_border){}

	Point get_head_position()const;
	std::vector<Point> get_snake()const;
	size_t length()const;
	void draw()const;

	void set_head_position(Point position);

	void increase(size_t size);
	void reduce(size_t size);

	void go_up();
	void go_down();
	void go_left();
	void go_right();

	void move();
	void load_texture();
private:
	std::vector<Point> blocks_position;
	Direction direction;

	int x_border;
	int y_border;

	void check();
	void check_on_position();
	Point get_move_point()const;
};