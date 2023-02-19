#pragma once
#include <vector>
#include "edge.hpp"

class Graph final{
private:
	std::vector<Edge> edges;


public:

	Graph(const std::vector<Edge> & _edges);

	Graph(const std::vector<Point> & pts);

	Graph kruskal() const;

	const std::vector<Edge> & get_edges() const;

};
