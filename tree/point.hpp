#pragma once
#include <sstream>
#include <string>
#include <cmath>
#include <vector>

using idt = int;

class Point final{
private:
	idt id{-1};
	float x{NAN}, y{NAN};
public:
	Point() = default;
	Point(idt id, float x, float y);

	bool operator==(const Point & a) const;
	bool operator!=(const Point & a) const;

	bool isvalid() const;

	static float distance(const Point & p1, const Point & p2);
	idt getid() const;
	float getx() const;
	float gety() const;
};
