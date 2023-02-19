#include "point.hpp"
#include <exception>
#include <iostream>


Point::Point(idt id, float x, float y) : id(id), x(x), y(y){
}

bool Point::operator==(const Point & a) const{
	return id == a.id && x == a.x && y == a.y;
}

bool Point::operator!=(const Point & a) const{
	return !(*this == a);
}

bool Point::isvalid() const{
		return std::isfinite(x) && std::isfinite(y) && (id > 0);
}

float Point::distance(const Point & p1, const Point & p2){
	if(!p1.isvalid() || !p2.isvalid())
		throw std::invalid_argument("one of points is invalid");
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

idt Point::getid() const{
	return id;
}

float Point::getx() const{
	return x;
}

float Point::gety() const{
	return y;
}
