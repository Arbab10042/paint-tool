#pragma once
#include "polygon.h"
#include"GP142.H"
class rectangle :public polygon
{
public:
	rectangle(Point p1, Point p2, int clr);
	bool contains(Point p);
	void fill(int clr);
	void draw();
private:
};

