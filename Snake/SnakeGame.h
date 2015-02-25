#pragma once
#include "Snake.h"
#include "GoodItem.h"
#include "BadItem.h"
#include "Item.h"
#include "Field.h"
#include "Menu.h"

#include <vector>
#include <glut.h>
#include <map>

class SnakeGame{
public:
	SnakeGame(size_t size_x, size_t size_y, size_t width, size_t height, size_t snake_size,
		size_t amount_of_good_item, size_t  amount_of_bad_item);

	void start_game(int argc, char **argv);
	void end_game();
private:
	Field field;
	Snake snake;
	std::vector<Item*> items;
	static SnakeGame *static_this;
	std::map<Point, bool> items_coord;

	void check_on_food();
	Item* generate_good_item();
	Item* generate_bad_item();

	void initialize_gl();
	void reshape_gl(int width, int height);
	void keyboard_gl_for_game(unsigned char key, int x, int y);
	void special_keyboard_gl_for_game(int key, int x, int y);
	void timer_gl(int);
	void draw_gl();
	void setupCur();

	static void draw();
	static void reshape(int width, int height);
	static void keyboard_for_game(unsigned char key, int x, int y);
	static void special_keyboard_for_game(int key, int x, int y);
	static void timer(int);
};