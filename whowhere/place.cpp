#include "place.hpp"

Place::Place(const std::string & _name, int x1, int y1, int x2, int y2){
	name = _name;
	l = std::min(x1, x2);
	r = std::max(x1, x2);
	u = std::min(y1, y2);
	d = std::max(y1, y2);
}

bool Place::in(int x, int y) const{
	return (l <= x) && (x <= r) && (u <= y) && (y <= d);
}
