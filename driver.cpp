
/*
 * CSE/ENGR 142 GP142_Demo
 *
 * 1/25/95
 * Author(s):         Larry Ruzzo
 * Email Address(s):  ruzzo@cs.washington.edu
 *
 * This program is a demo of some of the features of
 * GP142 --- the CSE/ENGR 142 Graphics Package.
 * It includes simple drawing commands, keyboard and mouse
 * interaction, and a simple animation.
 *
 * Revision history:
 * 11/18/97 Dan Boren  - Removed calls to obsolete function GP142_undo()
 *
 */

#include <stdio.h>
#include <math.h>
#include<iomanip>
#include <queue>
#include<string>
#include<fstream>
#include<vector>
#include "GP142.h"
#include"Shape.h"
#include"OpenShape.h"
#include"line.h"
#include"curve.h"
#include"circle.h"
#include"text.h"
#include"polygon.h"
#include"rectangle.h"

#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
#define TEXT_SIZE 20

int row[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
int col[] = { -1,  0,  1, -1, 1, -1, 0, 1 };

using namespace std;

//You will use the following 5 functions do to all work

//A) DRAWING FUNCTIONS
//the two drawing functions that you will use to make all shapes
void draw_line(int x1, int y1, int x2, int y2, int color = BLACK, int width = 1) {
	GP142_lineXY(color, x1, y1, x2, y2, width);
}

void draw_circle(int x, int y, int radius, int color = BLACK) {
	GP142_circleXY(color, x, y, radius);
}

//B) EVENT HANDLERS
//Mouse handler
void handle_mouse(int x, int y) {
	GP142_printfXY(WHITE, x, y, 9, "(%d,%d)", x, y);
}

//Keyboard handler
void handle_kbd(char c)
{
	//put the character anywhere you want to.
	//I'm putting it on the origin
	GP142_printfXY(BLACK, 0, 0, TEXT_SIZE, "%c", c);
}

//periodic handler you will not need to use because we're not doing animation
void demo_handle_periodic(void) {};

void PrintCanvas()
{
	Point p1, p2;
	p1.x = -490;	p1.y = 340;
	p2.x = 674;		p2.y = -333;
	rectangle* canvas = new rectangle(p1, p2, 1);
	canvas->draw();
	canvas->fill(WHITE);
	delete canvas;
}

rectangle* printBoundary()
{
	Point O;
	O.x = 0;	O.y = 0;
	Point topLeft = O, botRight = O;
	topLeft.x = -679;	topLeft.y = 340;
	botRight.x = -490;	botRight.y = -333;
	draw_line(-490, 340, -490. - 333, 0);
	rectangle* rect = new rectangle(topLeft, botRight, 1);
	rect->draw();
	return rect;
}

//Options for menu Panel
vector<rectangle*> printMenu()
{
	Point p1, p2;
	vector<rectangle*> shape;
	int  x1 = -660, x2 = -600, y1 = 320, y2 = 260;
	for (int i = 0, count = 0; i < 11; i++,count++)		//Boxes allocation
	{
		if (count % 2 != 0)
		{
			x1 += 80;
			x2 += 80;
		}
		if (count != 0 && count % 2 == 0)
		{
			y1 -= 80;
			y2 -= 80;
		}
		p1.x = x1;	p1.y = y1;		p2.x = x2;	p2.y = y2;
		shape.push_back(new rectangle(p1, p2, 1));
		shape[i]->draw();
		x1 = -660;	x2 = -600;
	}
	return shape;
}

void setArray(vector<Shape*>& shapes)
{
	int index = 0;
	for (int i = 0; i < shapes.size(); i++)
	{
		if (shapes[i] == nullptr)
		{
			index = i;
			break;
		}
	}
	for (int i = index; i < shapes.size(); i++)
	{
		swap(shapes[index], shapes[i]);
		index++;
	}
	shapes.pop_back();
}

void WhiteEraser()
{
	vector<Point>points;
	points.resize(4);
	points[0].x = -627;		points[0].y = -11;
	points[1].x = -651;		points[1].y = -35;
	points[2].x = -627;		points[2].y = -41;
	points[3].x = -606;		points[3].y = -16;
	polygon era(points, 1);				//Eraser
	era.draw();
	draw_line(-651, -35, -651, -45, 1);
	draw_line(-627, -41, -627, -51, 1);
	draw_line(-651, -45, -627, -51, 1);
	draw_line(-606, -16, -606, -26, 1);
	draw_line(-606, -26, -627, -51, 1);
}

void RedEraser()
{
	vector<Point>points;
	points.resize(4);
	points[0].x = -627;		points[0].y = -11;
	points[1].x = -651;		points[1].y = -35;
	points[2].x = -627;		points[2].y = -41;
	points[3].x = -606;		points[3].y = -16;
	polygon era(points, RED);				//Eraser
	era.draw();
	draw_line(-651, -35, -651, -45,RED);
	draw_line(-627, -41, -627, -51,RED);
	draw_line(-651, -45, -627, -51,RED);
	draw_line(-606, -16, -606, -26,RED);
	draw_line(-606, -26, -627, -51,RED);
}

void fillMenu()
{
	Point p1, p2, p3;
	vector<char> opt;
	vector<Point>points;
	draw_line(-648, 309, -611, 272, 1);		//Line	[0]
	points.resize(3);
	p1.x = -550;	p1.y = 311;
	p2.x = -534;	p2.y = 275;
	p3.x = -570;		p3.y = 275;
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
	polygon TRI(points, 1);				//Triangle	[1]
	TRI.draw();
	
	points.resize(4);
	points[0].x = -628;		points[0].y = 223;
	points[1].x = -648;		points[1].y = 214;
	points[2].x = -637;		points[2].y = 201;
	points[3].x = -610;		points[3].y = 195;
	curve c(points, 1);						//Curve	[2]
	c.draw();
	
	points[0].x = -560;		points[0].y = 224;
	points[1].x = -566;		points[1].y = 196;
	points[2].x = -531;		points[3].y = 221;
	points[3].x = -528;		points[2].y = 194;
	polygon p(points, 1);					//Polygon	[3]
	p.draw();
	
	p1.x = -648;	p1.y = 148;
	p2.x = -613;	p2.y = 114;
	rectangle r(p1, p2, 1);					//Retangle	[4]
	r.draw();
	
	p1.x = -620;	p1.y = 130;
	p1.x = -552;	p1.y = 130;
	circle cir(p1, 20, 1, -1);				//Circle	[5]
	cir.draw();
	
	GP142_printfXY(WHITE, -645, 20, 50, "%c", 'T');		//Text	[6]
	
	GP142_printfXY(WHITE, -578, 24, 50, "%c", 'F');		//Fill	[7]
	GP142_printfXY(WHITE, -550, 24, 50, "%c", 'i');		
	GP142_printfXY(WHITE, -543, 24, 50, "%c", 'l');		
	GP142_printfXY(WHITE, -535, 24, 50, "%c", 'l');		
	
	WhiteEraser();				//Eraser[8]
	
	GP142_printfXY(WHITE, -577, -40, 25, "%c", 'S');		//Save	[9]
	GP142_printfXY(WHITE, -560, -40, 25, "%c", 'a');
	GP142_printfXY(WHITE, -545, -40, 25, "%c", 'v');
	GP142_printfXY(WHITE, -534, -40, 25, "%c", 'e');

	GP142_printfXY(WHITE, -653, -123, 25, "%c", 'L');		//Load [10]
	GP142_printfXY(WHITE, -640, -123, 25, "%c", 'o');
	GP142_printfXY(WHITE, -627, -123, 25, "%c", 'a');
	GP142_printfXY(WHITE, -615, -123, 25, "%c", 'd');
}

vector<rectangle*> fillColors(rectangle *&rect)
{
	Point p1, p2;
	p1.x = -490;		p1.y = -210;
	p2.x = -110;			p2.y = -333;
	rect = new rectangle(p1, p2, 1);
	rect->draw();
	rect->fill(BLACK);
	vector < rectangle*>shapes;
	int x1 = -475, y1 = -230, x2 = -435, y2 = -260;
	for (int i = 0; i < 12; i++)		//Boxes allocation
	{
		if (i != 6 && i != 0)
		{
			x1 += 60;
			x2 += 60;
		}
		else if (i == 6)
		{
			y1 -= 50;
			y2 -= 50;
			x1 = -475;	
			x2 = -435;
		}
		p1.x = x1;		p1.y = y1;
		p2.x = x2;		p2.y = y2;
		shapes.push_back(new rectangle(p1, p2, 1));
		shapes[i]->draw();
	}
	shapes[1]->fill(WHITE);
	shapes[2]->fill(RED);
	shapes[3]->fill(GREEN);
	shapes[4]->fill(YELLOW);
	shapes[5]->fill(MAGENTA);
	shapes[6]->fill(CYAN);
	shapes[7]->fill(PURPLE);
	shapes[8]->fill(ICE_BLUE);
	shapes[9]->fill(PINK);
	shapes[10]->fill(ORANGE);
	shapes[11]->fill(BROWN);
	return shapes;
}

void save(const vector<Shape*>& shapes)
{
	ofstream fout("Drawing.pdb");
	vector<Point>points;
	vector<char>words;
	for (int i = 0; i < shapes.size(); i++)
	{
		fout << typeid(*(shapes[i])).name() << ",";
		if (strcmp(typeid(*(shapes[i])).name(), "class line") == 0)
			fout << shapes[i]->getStyle() << ",";
		points = shapes[i]->getPoints();
		if (strcmp(typeid(*(shapes[i])).name(), "class curve") == 0 || strcmp(typeid(*(shapes[i])).name(), "class polygon") == 0)
			fout << points.size() << ",";
		for (int i = 0; i < points.size(); i++)
		{
			fout << points[i].x << "," << points[i].y << ",";
		}
		if (strcmp(typeid(*(shapes[i])).name(), "class circle") == 0)
			fout << shapes[i]->getRadius() << ",";
		fout << shapes[i]->getColor();
		if (strcmp(typeid(*(shapes[i])).name(), "class text") == 0)
		{
			fout << ",";
			words = shapes[i]->getText();
			for (int i = 0; i < words.size(); i++)
				fout << words[i];
			fout << endl;
		}
		else
			fout << endl;
	}
	fout.close();
}

void load(vector<Shape*>& shapes)
{
	ifstream fin("Drawing.pdb");
	int count = 0;
	Point p1, p2;
	int color, ind = 0, noOfPoints, coord;
	double radius;
	bool style;
	vector<int>points;
	string className;
	vector<char>words;
	string temp;
	while (getline(fin, className))
		count++;
	fin.clear();
	fin.seekg(0);
	for (int i = 0; i < count; i++)
	{
		if (i > 0)
			fin.ignore();
		getline(fin, className, ',');
		if (className.compare("class line") == 0 || className.compare("class rectangle") == 0)
		{
			if (className.compare("class line") == 0)
				fin >> style;
			fin.ignore();
			fin >> p1.x;
			fin.ignore();
			fin >> p1.y;
			fin.ignore();
			fin >> p2.x;	
			fin.ignore();
			fin >> p2.y;
			fin.ignore();
			fin >> color;
			if (className.compare("class line") == 0)
				shapes.push_back(new line(p1, p2, color, style));
			else if (className.compare("class rectangle") == 0)
				shapes.push_back(new rectangle(p1, p2, color));
		}
		else if (className.compare("class circle") == 0)
		{
			fin >> p1.x;
			fin.ignore();
			fin >> p1.y;
			fin.ignore();
			fin >> radius;
			fin.ignore();
			fin >> color;
			shapes.push_back(new circle(p1, radius, color, -1));
		}
		else if (className.compare("class text") == 0)
		{
			fin >> p1.x;
			fin.ignore();
			fin >> p1.y;
			fin.ignore();
			fin >> color;
			fin.ignore();
			getline(fin, temp);
			for (int j = 0; j < temp.size(); j++)
				words.push_back(temp[j]);
			shapes.push_back(new text(p1, color, words));
		}
		else if (className.compare("class curve") == 0 || className.compare("class polygon") == 0)
		{
			fin >> noOfPoints;
			fin.ignore();
			for (int j = 0; j < noOfPoints * 2; j++)
			{
				fin >> coord;
				points.push_back(coord);
				fin.ignore();
			}
			fin >> color;
			if (className.compare("class curve") == 0)
				shapes.push_back(new curve(points, color));
			else if (className.compare("class polygon") == 0)
				shapes.push_back(new polygon(points, color));
			points.resize(0);
		}
		if (shapes.size() != 0)
			shapes[ind]->draw();
		ind++;
	}
	fin.close();
}

void Eraser(Point p, vector<Shape*>& shapes,int &ShapeSize)
{
	int size = shapes.size();
	int i = size - 1;
	Point p1, p2;
	vector<Point>points;
	vector<char>words;
	bool deleted = false;
	Shape* temp = nullptr;
	for (; i >= 0; i--)
	{
		
		if (shapes[i]->contains(p) && shapes[i] != nullptr)
		{
			points = shapes[i]->getPoints();
			if (strcmp(typeid(*(shapes[i])).name(), "class line") == 0 || strcmp(typeid(*(shapes[i])).name(), "class rectangle") == 0)
			{
				p1 = points[0];
				p2 = points[1];
				if (strcmp(typeid(*(shapes[i])).name(), "class line") == 0)
					temp = new line(p1, p2, 1, shapes[i]->getStyle());
				else
					temp = new rectangle(p1, p2, 1);
				temp->draw();
				deleted = true;
				break;
			}
			else if (strcmp(typeid(*(shapes[i])).name(), "class circle") == 0 || strcmp(typeid(*(shapes[i])).name(), "class text"))
			{
				p1 = points[0];
				if (strcmp(typeid(*(shapes[i])).name(), "class circle") == 0)
				{
					temp = new circle(p1, shapes[i]->getRadius(), 1, -1);
					temp->draw();
				}
				else if (strcmp(typeid(*(shapes[i])).name(), "class text") == 0)
				{
					temp = new text(p1, 1, shapes[i]->getText());
					temp->draw();
				}
				deleted = true;
				break;
			}
			else if (strcmp(typeid(*(shapes[i])).name(), "class polygon") == 0)
			{
				temp = new polygon(points, 1);
				temp->draw();
				deleted = true;
				break;
			}
			else if (strcmp(typeid(*(shapes[i])).name(), "class curve") == 0)
			{
				temp = new curve(points, 1);
				deleted = true;
				temp->draw();
				break;
			}
		}
	}
	if (deleted)
	{
		delete temp;
		delete shapes[i];
		shapes[i] = nullptr;
		setArray(shapes);
		ShapeSize--;
		for (int j = 0; j < shapes.size(); j++)
			if (shapes[j] != nullptr)
				shapes[j]->draw();
	}
}

bool isSafe(Shape * obj,int x,int y,int clr)
{
	Point p;
	p.x = x;	p.y = y;
	if (obj->contains(p))
	{
		if (Z_getPixel(x, y) == clr)
			return true;
		else
			return false;
	}
	else
		return false;
}

void floodfill(Shape* obj, int x, int y, int replacement)
{
	queue<pair<int, int>> q;
	q.push({ x, y });

	int target = Z_getPixel(x, y);

	while (!q.empty())
	{
		pair<int, int> node = q.front();
		q.pop();

		int x = node.first, y = node.second;

		GP142_pixelXY(replacement, x, y);

		for (int k = 0; k < 8; k++)
		{
			if (isSafe(obj,x + row[k], y + col[k], target))
			{
				q.push({ x + row[k], y + col[k] });
			}
		}
	}
}

/******************************************************************************
 *
 * The Main Program
 * ----------------
 *
 * The main program takes care of initialization and cleanup, and the high-level
 * control of all actions in the program, but most of the detail work is
 * relegated to sub-functions, so that the structure of main stays clear and
 * simple.
 *
 */

int main(void)
{
	int quit = 0, i = 0, color = 0;           /* has user signaled quit yet?                      */
	int pcount = 0;
	int mouse_x, mouse_y;
	char key_pressed;
	vector<int>temp;
	vector<char>words;
	Point option;
	Point p1, p2;
	vector<rectangle*>menu;
	vector<rectangle*>colorMenu;
	rectangle* colorBoundary;
	rectangle* boundary;
	vector<Shape*>shapes;
	bool redEraser = false, whiteEraser = true;
	bool rect, POLY, CIRCLE, LINE, TEXT, CURVE, TRI, ERASER, SAVE, LOAD;
	rect = POLY = CIRCLE = LINE = TEXT = CURVE = TRI = ERASER = SAVE = LOAD = false;
	GP142_open();           /* Open and initialize the GP142 Graphics Window    */
	PrintCanvas();
	boundary = printBoundary();
	menu = printMenu();			/*Prints menu and menu panel*/
	fillMenu();
	colorMenu = fillColors(colorBoundary);
	//The Event Loop
	while (!quit) {

		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
		case GP142_QUIT:
			quit = 1;   /* set flag to terminate loop                */
			break;

		case GP142_MOUSE:
			option.x = mouse_x;
			option.y = mouse_y;
			if (colorMenu[0]->contains(option))
			{
				color = BLACK;
			}
			else if (colorMenu[1]->contains(option))
			{
				color = WHITE;
			}
			else if (colorMenu[2]->contains(option))
			{
				color = RED;
			}
			else if (colorMenu[3]->contains(option))
			{
				color = GREEN;
			}
			else if (colorMenu[4]->contains(option))
			{
				color = YELLOW;
			}
			else if (colorMenu[5]->contains(option))
			{
				color = MAGENTA;
			}
			else if (colorMenu[6]->contains(option))
			{
				color = CYAN;
			}
			else if (colorMenu[7]->contains(option))
			{
				color = PURPLE;
			}
			else if (colorMenu[8]->contains(option))
			{
				color = ICE_BLUE;
			}
			else if (colorMenu[9]->contains(option))
			{
				color = PINK;
			}
			else if (colorMenu[10]->contains(option))
			{
				color = ORANGE;
			}
			else if (colorMenu[11]->contains(option))
			{
				color = BROWN;
			}
			if (menu[0]->contains(option) == true)
			{
				LINE = true;
				if (ERASER == true)
					LINE = false;
				rect = POLY = CIRCLE = TEXT = CURVE = ERASER = SAVE = LOAD = false;
			}
			else if (menu[1]->contains(option) == true)
			{
				TRI = true;
				if (ERASER == true)
					TRI = false;
				rect = POLY = CIRCLE = LINE = TEXT = CURVE = ERASER = SAVE = LOAD = false;
			}
			else if (menu[2]->contains(option) == true)
			{
				CURVE = true;
				if (ERASER == true)
					CURVE = false;
				rect = POLY = LINE = TEXT = CIRCLE = TRI = ERASER = SAVE = LOAD = false;
			}
			else if (menu[3]->contains(option) == true)
			{
				POLY = true;
				if (ERASER == true)
					POLY = false;
				rect = CIRCLE = LINE = TEXT = CURVE = TRI = ERASER = SAVE = LOAD = false;
			}
			else if (menu[4]->contains(option) == true)
			{
				rect = true;
				if (ERASER == true)
					rect = false;
				POLY = CIRCLE = LINE = TEXT = CURVE = TRI = ERASER = SAVE = LOAD = false;
			}
			else if (menu[5]->contains(option) == true)
			{
				CIRCLE = true;
				if (ERASER == true)
					CIRCLE = false;
				rect = POLY = LINE = TEXT = CURVE = TRI = ERASER = SAVE = LOAD = false;
			}
			else if (menu[6]->contains(option) == true)
			{
				TEXT = true;
				if (ERASER == true)
					TEXT = false;
				rect = POLY = CIRCLE = LINE = CURVE = TRI = ERASER = SAVE = LOAD = false;
			}
			else if (menu[8]->contains(option) == true)
			{
				if (ERASER == true)
				{
					ERASER = false;
					whiteEraser = true;
				}
				else
				{
					redEraser = true;
					ERASER = true;
					whiteEraser = false;
				}
				rect = POLY = CIRCLE = LINE = CURVE = TRI = TEXT = SAVE = LOAD = false;
			}
			else if (menu[9]->contains(option) == true)
			{
				SAVE = true;
				rect = POLY = CIRCLE = LINE = CURVE = TRI = TEXT = ERASER = LOAD = false;
			}
			else if (menu[10]->contains(option) == true)
			{
				LOAD = true;
				rect = POLY = CIRCLE = LINE = CURVE = TRI = TEXT = ERASER = SAVE = false;
			}

			if (ERASER == true)
			{
				RedEraser();
			}
			if (whiteEraser == true)
			{
				WhiteEraser();
				whiteEraser = redEraser = false;
			}
			
			if (LINE == true && ERASER == false)
			{
				if (boundary->contains(option) == false && colorBoundary->contains(option) == false)
				{
					temp.push_back(mouse_x);
					temp.push_back(mouse_y);
					pcount++;
				}
				if (pcount == 2)
				{
					p1.x = temp[0];		p1.y = temp[1];
					p2.x = temp[2];		p2.y = temp[3];
					shapes.push_back(new line(p1, p2, color, true));
					shapes[i]->draw();
					i++;
					pcount = 0;
					temp.resize(0);
				}
			}
			else if (TRI == true && ERASER == false)
			{
				if (boundary->contains(option) == false && colorBoundary->contains(option) == false)
				{
					temp.push_back(mouse_x);
					temp.push_back(mouse_y);
					pcount++;
				}
				if (pcount == 3)
				{
					shapes.push_back(new polygon(temp, color));
					shapes[i]->draw();
					i++;
					pcount = 0;
					temp.resize(0);
				}
			}
			else if (CURVE == true && ERASER == false)
			{
				if (boundary->contains(option) == false && colorBoundary->contains(option) == false)
				{
					temp.push_back(mouse_x);
					temp.push_back(mouse_y);
				}
			}
			else if (POLY == true && ERASER == false)
			{
				if (boundary->contains(option) == false && colorBoundary->contains(option) == false)
				{
					temp.push_back(mouse_x);
					temp.push_back(mouse_y);
				}
			}
			else if (rect == true && ERASER == false)
			{
				if (boundary->contains(option) == false && colorBoundary->contains(option) == false)
				{
					temp.push_back(mouse_x);
					temp.push_back(mouse_y);
					pcount++;
				}
				
				if (pcount == 2)
				{
					p1.x = temp[0];		p1.y = temp[1];
					p2.x = temp[2];		p2.y = temp[3];
					shapes.push_back(new rectangle(p1, p2, color));
					shapes[i]->draw();
					i++;
					pcount = 0;
					temp.resize(0);
				}
			}
			else if (CIRCLE == true && ERASER == false)
			{
				if (boundary->contains(option) == false && colorBoundary->contains(option) == false)
				{
					temp.push_back(mouse_x);
					temp.push_back(mouse_y);
					pcount++;
				}
				if (pcount == 2)
				{
					double rad = sqrt(pow(temp[2] - temp[0], 2) + pow(temp[3] - temp[1], 2) * 1.0);
					p1.x = temp[0];		p1.y = temp[1];
					shapes.push_back(new circle(p1, rad, color, -1));
					shapes[i]->draw();
					i++;
					pcount = 0;
					temp.resize(0);
				}
			}
			else if (TEXT == true && ERASER == false)
			{
				if (boundary->contains(option) == false && colorBoundary->contains(option) == false)
				{
					p1.x = mouse_x;
					p1.y = mouse_y;
				}
			}
			else if (ERASER == true)
			{
				if (boundary->contains(option) == false && colorBoundary->contains(option) == false)
				{
					p1.x = mouse_x;
					p1.y = mouse_y;
					pcount++;
				}
				if (pcount == 1)
				{
					Eraser(p1, shapes, i);
					pcount = 0;
				}
			}
			else if (SAVE)
			{
				save(shapes);
				SAVE = false;
			}
			else if (LOAD)
			{
				load(shapes);
				LOAD = false;
			}
			break;

		case GP142_KBD:
			//Keyboard handler
			if (TEXT == true && ERASER == false)
			{
				if (key_pressed != 13)
					words.push_back(key_pressed);
				else
				{
					shapes.push_back(new text(p1, color, words));
					shapes[i]->draw();
					i++;
					words.resize(0);
				}
			}
			else if (CURVE == true && ERASER == false)
			{
				shapes.push_back(new curve(temp, color));
				shapes[i]->draw();
				i++;
				temp.resize(0);
			}
			else if (POLY == true && ERASER == false)
			{
				shapes.push_back(new polygon(temp, color));
				shapes[i]->draw();
				i++;
				temp.resize(0);
			}
			break;

		default:
			break;
		}
	}
	GP142_close();
	/* Clean up and close graphics window           */
	
	delete boundary;
	delete colorBoundary;
	if (menu.size() != 0)
		for (int j = 0; j < menu.size(); j++)
			delete menu[j];
	if (colorMenu.size() != 0)
		for (int j = 0; j < colorMenu.size(); j++)
			delete colorMenu[j];
	for (int j = 0; j < shapes.size(); j++)
		if (shapes[j] != nullptr)
			delete shapes[j];
	return 0;
}