#pragma once
#include <string>

#include "point.hpp"

class Edge final{
private:
	Point from, to;
	float distance{0};

public:
	Edge(const Point & p1, const Point & p2);

	bool operator<(const Edge & a) const;
	bool operator==(const Edge & a) const;

	const Point & getfrom() const;
	const Point & getto() const;
	float getdistance() const;

};
