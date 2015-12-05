#include "Point.h"

Point::Point()
	:x(0), y(0)
{

}

Point::Point(float x, float y)
	:x(x), y(y)
{

}

Point::Point(float pos[2])
	: x(pos[0]), y(pos[1])
{

}

const Point& Point::operator-=(const Point& _Point)
{
	x -= _Point.x;
	y -= _Point.y;
	return *this;
}

Point Point::operator-(const Point& _Point) const
{
	Point point = *this;
	point -= _Point;
	return point;
}

const Point& Point::operator+=(const Point& _Point)
{
	x += _Point.x;
	y += _Point.y;
	return *this;
}

Point Point::operator+(const Point& _Point) const
{
	Point point = *this;
	point += _Point;
	return point;
}

bool Point::operator==(const Point& _Point) const
{
	return x == _Point.x && y == _Point.y;
}

const Point& Point::operator=(const Point& _Point)
{
	x = _Point.x;
	y = _Point.y;
	return *this;
}
