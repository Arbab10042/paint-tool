#pragma once
#include<vector>
struct Point
{
	double x, y;
};

using namespace std;

class Shape
{
public:
	virtual bool contains(Point p) = 0;
	virtual int getColor();
	virtual bool getStyle();
	virtual vector<Point> getPoints();
	virtual void draw() = 0;
	virtual double getRadius();
	virtual vector<char> getText();
	virtual ~Shape();
protected:
	Point* points;
	int color, noOfPoints;
};

