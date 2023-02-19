#pragma once

#include <vector>
#include <iostream>

#include "edge.hpp"
#include "point.hpp"

namespace IO{

std::vector<Point> parse(std::istream& input);
void print(std::ostream& output, const std::vector<Edge> & edges);

}
