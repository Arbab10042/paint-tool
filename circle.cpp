#include "circle.h"
#include<math.h>
#include"GP142.H"

void draw_circle(int x, int y, int radius, int color = WHITE);

circle::circle(Point p, double rad, int clr, int fc=-1)
{
	noOfPoints = 1;
	points = new Point;
	points->x = p.x;
	points->y = p.y;
	color = clr;
	radius = rad;
	fillColor = fc;
}


void circle::draw()
{
	draw_circle(points->x, points->y, radius, color);
	if (fillColor != -1)
		fill(fillColor);
}

double circle::getRadius()
{
	return radius;
}

bool circle::contains(Point p)
{
	if (sqrt((p.x-points->x ) * (p.x- points->x) + ( p.y- points->y) * ( p.y- points->y)) <= radius)
		return true;
	else
		return false;
}

void circle::fill(int clr)
{
	fillColor = clr;
	for (int i = 0; i < radius - 1; i++)
	{
		draw_circle(points->x, points->y, i, fillColor);
	}
}

