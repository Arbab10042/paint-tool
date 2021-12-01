#pragma once
#include "Shape.h"
#include<vector>
using namespace std;
class text :public Shape
{
public:
	text(Point p, int clr, const vector<char>& w);
	void draw();
	vector<char> getText();
	bool contains(Point p);
private:
	vector<char>words;
};

