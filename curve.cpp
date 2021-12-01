#include "curve.h"
#define WHITE 1

void draw_line(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1);

curve::curve(const vector<Point>& p, int clr)
{
	noOfPoints = p.size();
	points = new Point[noOfPoints];
	for (int i = 0, j = 0; i < noOfPoints; i++)
	{
		points[i].x = p[i].x;
		points[i].y = p[i].y;
	}
	color = clr;
}

curve::curve(const vector<int>& p, int clr)
{
	noOfPoints = p.size() / 2;
	points = new Point[noOfPoints];
	for (int i = 0, j = 0; i < noOfPoints; i++)
	{
		points[i].x = p[j];	j++;
		points[i].y = p[j];	j++;
	}
	color = clr;
}

void curve::draw()
{
	for (int i = 0; i < noOfPoints - 1; i++)
		draw_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, color);
}

bool curve::contains(Point p)
{
	bool found = false;
	for (int i = 0; i < noOfPoints - 1 && found == false; i++)
	{
		if (pointLiesOnLine(points[i], points[i + 1], p))
			found = true;
	}
	return found;
}

void curve::changeColor(int clr)
{
	color = clr;
	curve::draw();
}

