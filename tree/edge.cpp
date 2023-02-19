#include "dsu.hpp"
#include "edge.hpp"

Edge::Edge(const Point & p1, const Point & p2){
	if(!p1.isvalid() || !p2.isvalid())
		throw std::invalid_argument("one of points is invalid");

	from = p1;
	to = p2;
	distance = Point::distance(p1, p2);
}

bool Edge::operator<(const Edge& a) const{
	return distance < a.distance;
}

bool Edge::operator==(const Edge& a) const{
	return distance == a.distance && from == a.from && to == a.to;
}

const Point & Edge::getfrom() const{
	return from;
}
const Point & Edge::getto() const{
	return to;
}
float Edge::getdistance() const{
	return distance;
}
