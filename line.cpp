#include "line.h"
#include<cmath>
#include <math.h>
#include"GP142.H"
#define WHITE 1

void draw_line(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1);

line::line(Point p1, Point p2, int clr,bool st)
{
	style = st;
	color = clr;
	noOfPoints = 2;
	points = new Point[noOfPoints];
	points[0].x = p1.x;	points[0].y = p1.y;
	points[1].x = p2.x;	points[1].y = p2.y;
}

void line::draw()
{
	if (style == true)
		draw_line(points[0].x, points[0].y, points[1].x, points[1].y, color);
	else
		dotted_line(points[0], points[1], color);
}

bool line::getStyle()
{
	return style;
}

bool line::contains(Point p)
{
	if ((p.x == points[0].x && p.y == points[0].y) || (p.x == points[1].x && p.y == points[1].y))
		return true;
	if (pointLiesOnLine(points[0], points[1], p))
		return true;
	return false;
}

void line::changeColor(int clr)
{
	color = clr;
	line::draw();
}

void line::dotted_line(Point a, Point b,int clr){
	float slope, intercept;
	int count = 0;
	double dx, dy;
	double left, top, right, bottom;
	dx = abs(b.x - a.x);
	dy = abs(b.y - a.y);
	if (a.x < b.x)
	{
		left = a.x;
		right = b.x;
	}
	else
	{
		left = b.x;
		right = a.x;
	}
	if (a.y < b.y)
	{
		top = a.y;
		bottom = b.y;
	}
	else
	{
		top = b.y;
		bottom = a.y;
	}
	if (left == right)
		slope = -1;
	else if (top == bottom)
		slope = 1;
	else
		slope = dy / dx;
	intercept = a.y - slope * a.x;
	if (slope == -1)
	{
		for (int i = top; i <= bottom; i+=2)
			GP142_pixelXY(3, left, i);
	}
	else if (slope == 1)
	{
		for (int i = left; i <= right; i += 2)
			GP142_pixelXY(3, i, left);
	}
	else
	{
		int inc_dec = ((b.y >= a.y) ? 1 : -1);
		if (dx > dy)
		{
			int two_dy = (2 * dy);
			int two_dy_dx = (2 * (dy - dx));
			int p = ((2 * dy) - dx);
			int x = a.x;
			int y = a.y;
			GP142_pixelXY(color, x, y);
			while (x < b.x)
			{
				x++;
				if (p < 0)
					p += two_dy;
				else
				{
					y += inc_dec;
					p += two_dy_dx;
				}
				if ((count % 2) != 0)
					GP142_pixelXY(color, x, y);
				count++;
			}
		}
		else
		{
			int two_dx = (2 * dx);
			int two_dx_dy = (2 * (dx - dy));
			int p = ((2 * dx) - dy);
			int x = a.x;
			int y = a.y;
			GP142_pixelXY(color, x, y);
			while (y != b.y)
			{
				y += inc_dec;

				if (p < 0)
					p += two_dx;
				else
				{
					x++;
					p += two_dx_dy;
				}
				if ((count % 2) != 0)
					GP142_pixelXY(color, x, y);
				count++;
			}
		}
	}
}
