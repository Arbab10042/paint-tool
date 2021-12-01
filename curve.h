#pragma once
#include<vector>
#include "OpenShape.h"
using namespace std;
class curve :public OpenShape
{
public:
	curve(const vector<Point>& p, int clr);
	curve(const vector<int>& p, int clr);
	void draw();
	bool contains(Point p);
	void changeColor(int clr);
};

