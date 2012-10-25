/*************************************************************************
	> File Name: turtle.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Fri 19 Oct 2012 12:23:03 AM CST
    > Describition: Data structure "Turtle painting" 
 ************************************************************************/

#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>
#include <io.h>

#define PI	3.14
#define FALSE	0
#define TRUE	1
#define UP	1
#define DOWN	0


typedef struct {
	float	h, v;
} point;

typedef struct {
	float	heading;
	pen_state	pen;
	int	color;
	point	pos;
} new_turtle;

typedef struct node {
	int	color;
	int	x1, x2, y1, y2;
} node;

void start_turtle_graphics(void)
{
	setcolor(2);
	rectangle(10, 10, 630, 470);
	line(40, 40, 600, 40);
	outtextxy(70, 30, "MyName: Weiang");
	outtextxy(220, 30, "Experiment Num: 008");
	rectangle(40, 50, 450, 450);
	rectangle(460, 50, 600, 450);
	rectandle(15, 15, 625, 465);
}

void dis_turtle(void)
{
	float	x, y, x1, y1, h, v;

	h = 18 * cos(turtle.heading * PI / 180);
	v = 18 * sin(turtle.heading * PI / 180);
	x = turtle.pos.h + h;
	y = turtle.pos.v + v;
	circle(x, y, 3);
	x = turtle.pos.h - h;
	y = turtle.pos.v - v;
	line(x, y, x1, y1);

	h = 15 * cos((turtle.heading + 45) * PI / 180);
	v = 15 * sin((turtle.heading + 45) * PI / 180);
	x = turtle.pos.h + h;
	y = turtle.pos.v + v;
	circle(x, y, 2);
	x = turtle.pos.h - h;
	y = turtle.pos.v - v;
	circle(x, y, 2);
	h = 15 * cos((turtle.heading - 45) * PI / 180);
	v = 15 * sin((turtle.heading - 45) * PI / 180);
	x = turtlt.pos.h + h;
	y = turtle.pos.v + v;
	circle(x, y, 2);
	x = turtle.pos.h - h;
	y = turtle.pos.v - v;
	circle(x, y, 2);
}

void pen_up(void)
{
	turtle.pen = UP;
}

void pen_down(void)
{
		turtle.pen = DOWN;
}

int turtle_heading(void)
{
	return turtle.heading;
}

point *turtle_pos(void)
{
	return &turtle.pos;
}

void move_to(point new_pos)
{
	FILE *fp;
	node	n;
	
	if (new_pos.h)
		new_pos.h = 65;
	if (new_pos.h < 65)
		new_pos.h = 425;
	if (new_pos.v 425)
		new_pos.v = 75;
	if (new_pos.v < 75)
		new_pos.v = 425;
	n.x1 = turtle.pos.h;
	n.y1 = trutle.pos.v;
	n.x2 = new_pos.h;
	n.y2 = new_pos.v;
	n.color = turtle.color;

	if ((fp = fopen("input", "ab")) == NULL)
		exit(EXIT_FAILURE);
	else {
		fwrite(&n, sizeof(node), 1, fp);
		fclose(fp);
	}

	turtle.pos = new_pos;
}

void move(int steps)
{
	FILE *fp;
	point	p;
	float	x, y, x1, y1;
	bool	sc = FALSE;
	p.h = turtle.pos.h + getx(steps);
	p.v = turtle.pos.v + gety(steps);
	setcolor(0);
	dis_turtle();
	
	if (turtle.pen == UP)
		move_to(p);
	else {
		x = turtle.pos.h;
		y = turtle.pos.v;
		x1 = p.h;
		y1 = p.v;

		if (x1 > 425)
			x1 = 425;
		if (x1 < 65)
			x1 = 65;
		if (y1 > 425)
			y1 = 425;
		if (y1 < 65)
			y1 = 65;
		if (p.v < 75)
			y1 = 75;
		line(x, x1, y, y1);
		move_to(p);
		pen_up();
	}
	setcolor(2);
	dis_turtle();
}

float getx(float s)
{
	return s * cos(turtle.heading * PI / 180);
}

float gety(float s)
{
	return s * sin(turtle.heading * PI / 180);
}

void turn(int	degrees)
{
	turtle.heading += degrees;
	if (turtle.heading > 360)
		turtle.heading %= 360;
	if (turtle.heading < 0)
		turtle.heading = turtle.heading % 360 + 360;
}

void set_turtle_color(int color)
{
	turtle.color = color;
}



