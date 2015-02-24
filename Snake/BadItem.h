#pragma once
#include "Item.h"
#include "Point.h"

class BadItem:public Item{
public:
	BadItem(Point position) :position(position){}
	BadItem() :position(Point()){}

	virtual Effect get_effect()const;
	virtual Point get_position()const;
	virtual void draw()const;
private:
	Point position;
};