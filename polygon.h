#pragma once

#include "Shape.h"
#include "Shape.h"
# include<math.h>
#include<stdlib.h>
#include<algorithm>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include<vector>

#define W 1

using namespace std;

const double epsilon = numeric_limits<float>().epsilon();
const double MIN = 0;
const double MAX = 2000000;

class polygon :public Shape
{
public:
	polygon();
	polygon(const vector<Point>& p, int clr);
	polygon(const vector<int>& p, int clr);
	bool contains(Point p);
	void fill(int clr);
	void draw();
protected:
	struct Edge {
		Point a, b;
		bool operator()(const Point& p) const;
	};
	int fillColor;
};

