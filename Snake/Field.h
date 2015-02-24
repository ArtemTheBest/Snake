#pragma once

class Field{
public:
	Field() :size_x(0), size_y(0), width(0), height(0){}
	Field(size_t size_x, size_t size_y, size_t width, size_t height):
		size_x(size_x), size_y(size_y), width(width), height(height){}

	size_t get_size_x()const;
	size_t get_size_y()const;
	size_t get_width()const;
	size_t get_height()const;

	void set_width(size_t width);
	void set_height(size_t length);

	void draw()const;
private:
	size_t size_x;
	size_t size_y;
	size_t width;
	size_t height;
};