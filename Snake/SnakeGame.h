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
	std::map<Point, bool> items_coord;
	Menu main_menu;
	Menu pause_menu;

	static Menu *static_menu;
	static SnakeGame *static_this;

	void check_on_food();
	Item* generate_good_item();
	Item* generate_bad_item();
	
	void menu_options(int cur);

	void main_menu_options(int cur);
	void pause_menu_options(int cur);

	void use_main_menu();
	void use_game();

	void initialize_snake();
	void reshape_snake(int width, int height);
	void keyboard_snake(unsigned char key, int x, int y);

	void keyboard_main_menu_gl(unsigned char key, int x, int y);

	void special_keyboard_snake(int key, int x, int y);
	void timer_snake(int);
	void draw_snake();
	
	static void(*draw_func)();
	static void(*init_func)();
	static void(*keyboard_func)(unsigned char, int, int);
	static void(*special_keyboard_func)(int, int, int);
	static void(*reshape_func)(int, int);
	static void(*timer_func)(int);

	static void draw_game();
	static void draw_menu();
	static void init_game();
	static void init_menu();
	static void keyboard_game(unsigned char key, int x, int y);
	static void keyboard_menu(unsigned char key, int x, int y);
	static void special_keyboard_game(int key, int x, int y);
	static void special_keyboard_menu(int key, int x, int y);
	static void reshape_game(int width, int height);
	static void reshape_menu(int width, int height);
	static void timer_game(int);
	static void timer_menu(int);

	static void initialize_gl();
	static void draw();
	static void reshape(int width, int height);
	static void keyboard(unsigned char key, int x, int y);
	static void special_keyboard(int key, int x, int y);
	static void timer(int);
};