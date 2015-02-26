#include "SnakeGame.h"

SnakeGame *SnakeGame::static_this;

void(*SnakeGame::draw_func)();

void(*SnakeGame::init_func)();

void(*SnakeGame::keyboard_func)(unsigned char, int, int);

void(*SnakeGame::special_keyboard_func)(int, int, int);

void(*SnakeGame::reshape_func)(int,int);

void(*SnakeGame::timer_func)(int);

SnakeGame::SnakeGame(size_t size_x, size_t size_y, size_t width, size_t height, size_t snake_size,
	size_t amount_of_good_item, size_t  amount_of_bad_item){
	this->field = Field(size_x, size_y, width, height);
	this->snake = Snake(snake_size,size_x,size_y);
	this->static_this = this;

	this->use_general_menu();

	std::vector<std::string> temp = {"New Game","Options","Exit"};
	this->general_menu = Menu(temp,width,height);

	for (size_t i = 0; i < amount_of_good_item; i++)
		this->items.push_back(this->generate_good_item());

	for (size_t i = 0; i < amount_of_bad_item; i++)
		this->items.push_back(this->generate_bad_item());
}

void SnakeGame::start_game(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(this->field.get_width(), this->field.get_height());
	glutInitWindowPosition(100, 100);
	glutCreateWindow("<= Snake =>");

	this->init_func();
	glutDisplayFunc(&SnakeGame::draw);
	glutReshapeFunc(&SnakeGame::reshape);
	glutKeyboardFunc(&SnakeGame::keyboard);
	glutSpecialFunc(&SnakeGame::special_keyboard);
	glutTimerFunc(30, &SnakeGame::timer, 0);
	glutMainLoop();
}

void SnakeGame::end_game(){
	exit(0);
}

void SnakeGame::check_on_food(){
	for (size_t i = 0; i < this->items.size(); i++){
		if (this->items[i]->get_position() == this->snake.get_head_position()){
			this->items_coord[this->items[i]->get_position()] = false;

			switch (this->items[i]->get_effect()){
			case good:
				this->snake.increase(1);
				this->items[i] = this->generate_good_item();
				break;
			case bad:
				this->snake.reduce(1);
				this->items[i] = this->generate_bad_item();
				break;
			}
		}
	}
}

Item* SnakeGame::generate_bad_item(){
	Point randPoint(rand() % this->field.get_size_x(), rand() % this->field.get_size_y());

	while (this->items_coord[randPoint])
		randPoint = Point(rand() % this->field.get_size_x(), rand() % this->field.get_size_y());

	this->items_coord[randPoint] = true;
	return new BadItem(randPoint);
}

Item* SnakeGame::generate_good_item(){
	Point randPoint(rand() % this->field.get_size_x(), rand() % this->field.get_size_y());

	while (this->items_coord[randPoint])
		randPoint = Point(rand() % this->field.get_size_x(), rand() % this->field.get_size_y());

	this->items_coord[randPoint] = true;
	return new GoodItem(randPoint);
}

void SnakeGame::use_general_menu(){
	this->init_func = &SnakeGame::init_general_menu;
	this->init_func();
	this->draw_func = &SnakeGame::draw_general_menu;
	this->keyboard_func = &SnakeGame::keyboard_general_menu;
	this->special_keyboard_func = &SnakeGame::special_keyboard_general_menu;
	this->reshape_func = &SnakeGame::reshape_general_menu;
	this->timer_func = &SnakeGame::timer_general_menu;
}

void SnakeGame::use_game(){
	this->init_func = &SnakeGame::init_game;
	this->init_func();
	this->draw_func = &SnakeGame::draw_game;
	this->keyboard_func = &SnakeGame::keyboard_game;
	this->special_keyboard_func = &SnakeGame::special_keyboard_game;
	this->reshape_func = &SnakeGame::reshape_game;
	this->timer_func = &SnakeGame::timer_game;
}

void SnakeGame::initialize_snake(){
	glEnable(GL_TEXTURE_2D);
	glClearColor(0, 0, 0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, this->field.get_size_x(), 0, this->field.get_size_y(), -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SnakeGame::reshape_snake(int width, int height){
	field.set_width(width);
	field.set_height(height);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, this->field.get_size_x(), 0, this->field.get_size_y(), -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SnakeGame::keyboard_snake(unsigned char key, int x, int y){
	switch (key){
	case 27:
		this->end_game();
		break;
	}
}

void SnakeGame::keyboard_general_menu_gl(unsigned char key, int x, int y){
	switch (key){
	case 13:
		this->use_game();
		break;
	}
}

void SnakeGame::special_keyboard_snake(int key, int x, int y){
	switch (key){
	case GLUT_KEY_RIGHT:
		this->snake.go_right();
		break;
	case GLUT_KEY_LEFT:
		this->snake.go_left();
		break;
	case GLUT_KEY_UP:
		this->snake.go_up();
		break;
	case GLUT_KEY_DOWN:
		this->snake.go_down();
		break;
	}
}

void SnakeGame::timer_snake(int = 0){
	this->snake.move();
	this->check_on_food();
}

void SnakeGame::draw_snake(){
	this->field.draw();

	for (std::vector<Item*>::iterator itr = std::begin(this->items); itr != std::end(this->items); itr++)
		(*itr)->draw();

	this->snake.draw();
}

void SnakeGame::draw_game(){
	static_this->draw_snake();
}

void SnakeGame::draw_general_menu(){
	static_this->general_menu.draw();
}

void SnakeGame::draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	static_this->draw_func();

	glutSwapBuffers();
}

void SnakeGame::init_game(){
	static_this->initialize_snake();
}

void SnakeGame::init_general_menu(){
	static_this->general_menu.initialize_gl();
}

void SnakeGame::keyboard_game(unsigned char key, int x, int y){
	static_this->keyboard_snake(key,x,y);
}

void SnakeGame::keyboard_general_menu(unsigned char key, int x, int y){
	static_this->keyboard_general_menu_gl(key,x,y);
}

void SnakeGame::special_keyboard_game(int key, int x, int y){
	static_this->special_keyboard_snake(key, x, y);
}

void SnakeGame::special_keyboard_general_menu(int key, int x, int y){
	static_this->general_menu.special_keyboard(key, x, y);
}

void SnakeGame::reshape_game(int width, int height){
	static_this->reshape_snake(width,height);
}

void SnakeGame::reshape_general_menu(int width, int height){
	static_this->general_menu.reshape(width, height);
}

void SnakeGame::timer_game(int = 0){
	static_this->timer_snake(0);
}

void SnakeGame::timer_general_menu(int = 0){
	static_this->general_menu.timer(0);
}

void SnakeGame::reshape(int width, int height){
	static_this->reshape_func(width,height);
}

void SnakeGame::keyboard(unsigned char key, int x, int y){
	static_this->keyboard_func(key,x,y);
}

void SnakeGame::special_keyboard(int key, int x, int y){
	static_this->special_keyboard_func(key, x, y);
}

void SnakeGame::timer(int = 0){
	static_this->timer_func(0);
	static_this->draw();
	glutTimerFunc(100, &SnakeGame::timer, 0);
}