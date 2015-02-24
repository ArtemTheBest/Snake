#pragma once

struct Point{
	int x;
	int y;

	Point(){}
	Point(int x, int y) :x(x), y(y){}

	Point& operator+=(const Point&);
	Point& operator-=(const Point&);
};

Point operator+(const Point&, const Point&);

Point operator-(const Point&, const Point&);

bool operator==(const Point&, const Point&);

bool operator>(const Point&, const Point&);

bool operator<(const Point&, const Point&);