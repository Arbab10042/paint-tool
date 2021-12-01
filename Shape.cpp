#include "Shape.h"
int Shape::getColor()
{
	return color;
}
bool Shape::getStyle()
{
	return false;
}
vector<Point> Shape::getPoints()
{
	vector<Point>p;
	p.resize(noOfPoints);
	for (int i = 0; i < noOfPoints; i++)
	{
		p[i].x = points[i].x;
		p[i].y = points[i].y;
	}
	return p;
}
double Shape::getRadius()
{
	return 0.0;
}
vector<char> Shape::getText()
{
	return vector<char>();
}
Shape::~Shape()
{
	delete[]points;
}
