#include "text.h"
#include"rectangle.h"
#include"GP142.H"
#define TEXT_SIZE 20
#define MORE_SPACE words[i]=='m'||words[i]=='M'||words[i]=='w'||words[i]=='W'
#define MEDIUM_SPACE words[i]=='r'&&words[i]!=' '
#define LESS_SPACE words[i]=='i'|| words[i]=='I'||words[i]=='l'||words[i]=='j'||words[i]=='J' ||words[i]=='t'

text::text(Point p, int clr, const vector<char>& w)
{
	noOfPoints = 1;
	points = new Point;
	points->x = p.x;
	points->y = p.y;
	color = clr;
	words.resize(w.size() + 1);
	words = w;
}

void text::draw()
{
	int j = 0;
	for (int i = 0; i < words.size(); i++)
	{
		GP142_printfXY(color, points->x + j, points->y, TEXT_SIZE, "%c", words[i]);
		if (MORE_SPACE)
			j += 16;
		else if (MEDIUM_SPACE)
			j += 8;
		else if (LESS_SPACE)
			j += 5;
		else 
			j += 10;
	}
}

vector<char> text::getText()
{
	return words;
}

bool text::contains(Point p)
{
	Point p1, p2;
	p1.x = points->x;	p1.y = points->y;
	p2.x = points->x;	p2.y = points->y;
	rectangle check(p1, p2, 0);
	if (check.contains(p))
		return true;
	else
		return false;
}

