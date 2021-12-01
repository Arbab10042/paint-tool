#include "polygon.h"
using namespace std;


polygon::polygon()
{
	points=nullptr;
	noOfPoints = 0;
	fillColor = -1;
}

polygon::polygon(const vector<Point>& p, int clr) {
	noOfPoints = p.size();
	points = new Point[noOfPoints];
	for (int i = 0, j = 0; i < noOfPoints; i++)
	{
		points[i].x = p[i].x;
		points[i].y = p[i].y;
	}
	fillColor = -1;
	color = clr;
}

polygon::polygon(const vector<int> &p, int clr) {
	noOfPoints = p.size() / 2;
	points = new Point[noOfPoints];
	for (int i = 0, j = 0; i < noOfPoints; i++)
	{
		points[i].x = p[j];		j++;
		points[i].y = p[j];		j++;
	}
	fillColor = -1;
	color = clr;
}

void draw_line(int x1, int y1, int x2, int y2, int color = W, int width = 1);

void polygon::draw() {
	for (int i = 0; i < noOfPoints - 1; i++)
	{
		draw_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, color);
		if (i == noOfPoints - 2)
			draw_line(points[i + 1].x, points[i + 1].y, points[0].x, points[0].y, color);
	}
}

bool polygon::contains(Point p) {
	auto c = 0;
	vector<Edge> edges;
	edges.resize(noOfPoints);
	for (int i = 0; i < noOfPoints - 1; i++)
	{
		edges[i].a.x = points[i].x;
		edges[i].a.y = points[i].y;
		edges[i].b.x = points[i + 1].x;
		edges[i].b.y = points[i + 1].y;
		edges[i + 1].a.x = edges[i].b.x;
		edges[i + 1].a.y = edges[i].b.y;
		if (i == noOfPoints - 2)
		{
			edges[i + 1].b.x = points[0].x;
			edges[i + 1].b.y = points[0].y;
		}
	}
	for (auto e : edges) if (e(p)) c++;
	return c % 2 != 0;
	return 0;
}

void polygon::fill(int clr)
{
}

bool polygon::Edge::operator()(const Point& p) const
{
	if (a.y > b.y) return Edge{ b, a }(p);
	if (p.y == a.y || p.y == b.y) return operator()({ p.x, p.y + epsilon });
	if (p.y > b.y || p.y < a.y || p.x > max(a.x, b.x)) return false;
	if (p.x < min(a.x, b.x)) return true;
	auto blue = abs(a.x - p.x) > MIN ? (p.y - a.y) / (p.x - a.x) : MAX;
	auto red = abs(a.x - b.x) > MIN ? (b.y - a.y) / (b.x - a.x) : MAX;
	return blue >= red;
}

