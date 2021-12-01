#pragma once
#include "OpenShape.h"
class line :public OpenShape
{
public:
	line(Point p1, Point p2, int clr,bool st);
	void draw();
	bool getStyle();
	bool contains(Point p);
	void changeColor(int clr);
private:
	void dotted_line(Point a, Point b, int clr);
};

