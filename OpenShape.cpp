#include "OpenShape.h"



bool OpenShape::pointLiesOnLine(Point p1, Point p2, Point p3)
{
	float slope, intercept;
	float dx, dy;
	float left, top, right, bottom;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	slope = dy / dx;
	intercept = p1.y - slope * p1.x;
	if (p1.x < p2.x)
	{
		left = p1.x;
		right = p2.x;
	}
	else
	{
		left = p2.x;
		right = p1.x;
	}
	if (p1.y < p2.y)
	{
		top = p1.y;
		bottom = p2.y;
	}
	else
	{
		top = p2.y;
		bottom = p1.y;
	}
	if (slope * p3.x + intercept >= (p3.y - 0.8) && slope * p3.x + intercept <= (p3.y + 0.8))
	{
		if (p3.x >= left && p3.x <= right && p3.y >= top && p3.y <= bottom)
			return true;
		else
			return false;
	}
	else
		return false;
}

