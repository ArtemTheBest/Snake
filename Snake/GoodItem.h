#pragma once
#include "Item.h"
#include "Point.h"

class GoodItem :public Item{
public:
	GoodItem(Point position) :position(position){}
	GoodItem() :position(Point()){}

	virtual Effect get_effect()const;
	virtual Point get_position()const;
	virtual void draw()const;
private:
	Point position;
};