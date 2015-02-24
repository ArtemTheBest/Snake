#pragma once
#include "Point.h"

enum Effect{good,bad};

class Item{
public:
	virtual Point get_position()const = 0;
	virtual Effect get_effect()const = 0;
	virtual void draw()const = 0;
};