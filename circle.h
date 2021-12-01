#pragma once
#include "Shape.h"
class circle :public Shape
{
public:
	circle(Point p, double rad, int clr, int fc);
	void draw();
	double getRadius();
	bool contains(Point p);
	void fill(int clr);
private:
	int fillColor;
	double radius;
};

