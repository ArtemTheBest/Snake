#include "SnakeGame.h"

SnakeGame *SnakeGame::static_this = new SnakeGame();

SnakeGame::SnakeGame(size_t size_x, size_t size_y, size_t width, size_t height, size_t snake_size,
	size_t amount_of_good_item, size_t  amount_of_bad_item){
	this->field = Field(size_x, size_y, width, height);
	this->snake = Snake(snake_size,size_x,size_y);
	this->static_this = this;

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

	this->initialize_gl();
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

void SnakeGame::initialize_gl(){
	glEnable(GL_TEXTURE_2D);
	glClearColor(0, 0, 0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, this->field.get_size_x(), 0, this->field.get_size_y(), -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SnakeGame::reshape_gl(int width, int height){
	field.set_width(width);
	field.set_height(height);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, this->field.get_size_x(), 0, this->field.get_size_y(), -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SnakeGame::keyboard_gl(unsigned char key, int x, int y){
	switch (key){
	case 'e':
		this->end_game();
		break;
	}
}

void SnakeGame::special_keyboard_gl(int key, int x, int y){
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

void SnakeGame::timer_gl(int = 0){
	this->snake.move();
	this->draw_gl();
	this->check_on_food();
	glutTimerFunc(100, &SnakeGame::timer, 0);
}

void SnakeGame::draw_gl(){
	glClear(GL_COLOR_BUFFER_BIT);

	this->field.draw();

	for (std::vector<Item*>::iterator itr = std::begin(this->items); itr != std::end(this->items); itr++)
		(*itr)->draw();

	this->snake.draw();

	glutSwapBuffers();
}

void SnakeGame::draw(){
	static_this->draw_gl();
}

void SnakeGame::reshape(int width, int height){
	static_this->reshape_gl(width, height);
}

void SnakeGame::keyboard(unsigned char key, int x, int y){
	static_this->keyboard_gl(key, x, y);
}

void SnakeGame::special_keyboard(int key, int x, int y){
	static_this->special_keyboard_gl(key, x, y);
}

void SnakeGame::timer(int = 0){
	static_this->timer_gl();
}