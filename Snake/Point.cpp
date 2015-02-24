#include "Point.h"

Point operator+(const Point &p_1, const Point &p_2){
	return Point(p_1.x + p_2.x,p_1.y + p_2.y);
}

Point operator-(const Point &p_1, const Point &p_2){
	return Point(p_1.x - p_2.x, p_1.y - p_2.y);
}

Point& Point::operator+=(const Point &p){
	this->x += p.x;
	this->y += p.y;
	return *this;
}

Point& Point::operator-=(const Point &p){
	this->x -= p.x;
	this->y -= p.y;
	return *this;
}

bool operator==(const Point &p_1, const Point &p_2){
	return (p_1.x == p_2.x) && (p_1.y == p_2.y);
}

bool operator>(const Point &p_1, const Point &p_2){
	return p_1.x > p_2.x;
}

bool operator<(const Point &p_1, const Point &p_2){
	return p_1.x < p_2.x;
}