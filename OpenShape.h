#pragma once
#include "Shape.h"
class OpenShape :
	public Shape
{
public:
	virtual void changeColor(int clr) = 0;
protected:
	bool pointLiesOnLine(Point a, Point b, Point c);
	bool style;
};

