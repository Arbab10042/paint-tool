#include "rectangle.h"
using namespace std;

void draw_line(int x1, int y1, int x2, int y2, int color = W, int width = 1);

rectangle::rectangle(Point p1, Point p2, int clr)
{
	noOfPoints = 2;
	points = new Point[noOfPoints];
	points[0].x = p1.x;	points[0].y = p1.y;
	points[1].x = p2.x;	points[1].y = p2.y;
	color = clr;
	fillColor = -1;
}

bool rectangle::contains(Point p)
{
	Point O;
	O.x = 0;	O.y = 0;
	Point topL = O, botL = O, topR = O, botR = O;
	if (points[0].x < points[1].x && points[0].y > points[1].y)
	{
		topL.x = points[0].x;	topL.y = points[0].y;
		botR.x = points[1].x;	botR.y = points[1].y;
		topR.x = points[1].x;	topR.y = points[0].y;
		botL.x = points[0].x;	botL.y = points[1].y;
	}
	else if (points[1].x < points[0].x && points[1].y > points[0].y)
	{
		topL.x = points[1].x;	topL.y = points[1].y;
		botR.x = points[0].x;	botR.y = points[0].y;
		topR.x = points[0].x;	topR.y = points[1].y;
		botL.x = points[1].x;	botL.y = points[0].y;
	}
	else if (points[0].x > points[1].x && points[0].y > points[1].y)
	{
		topR.x = points[0].x;	topR.y = points[0].y;
		botR.x = points[0].x;	botR.y = points[1].y;
		topL.x = points[0].x;	topL.y = points[1].y;
		botL.x = points[1].x;	botL.y = points[1].y;
	}
	else if (points[1].x > points[0].x && points[1].y > points[0].y)
	{
		topR.x = points[1].x;	topR.y = points[1].y;
		botR.x = points[1].x;	botR.y = points[0].y;
		topL.x = points[1].x;	topL.y = points[0].y;
		botL.x = points[0].x;	botL.y = points[0].y;
	}
	if (p.x >= topL.x && p.x <= topR.x && p.y >= botR.y && p.y <= topR.y)
		return true;
	else
		return false;
}

void rectangle::fill(int clr)
{
	if (points[0].y < points[1].y)
		for (int i = points[0].y + 1; i < points[1].y - 1; i++)
			draw_line(points[0].x + 1, i, points[1].x, i, clr);
	else
	for (int i = points[1].y + 1; i < points[0].y - 1; i++)
			draw_line(points[0].x + 1, i, points[1].x, i, clr);
}

void rectangle::draw()
{
	draw_line(points[0].x, points[0].y, points[1].x, points[0].y, color);
	draw_line(points[1].x, points[0].y, points[1].x, points[1].y, color);
	draw_line(points[1].x, points[1].y, points[0].x, points[1].y, color);
	draw_line(points[0].x, points[1].y, points[0].x, points[0].y, color);
}



