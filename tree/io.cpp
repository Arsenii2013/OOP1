#include "io.hpp"
#include <iostream>
#include <exception>

std::vector<Point> IO::parse(std::istream& input){
	std::string s;

	std::vector<Point> res;
	while(getline(input, s)){
        idt id;
        float x;
        float y;
        char separator;

        std::istringstream iss(s);

        if (!(iss >> id) || !(iss >> separator) || separator != ',')
        	throw std::runtime_error(s);
        if (!(iss >> x) || !(iss >> separator) || separator != ',')
        	throw std::runtime_error(s);
        if (!(iss >> y))
        	throw std::runtime_error(s);

        res.push_back(Point(id, x, y));
	}
	return res;
}

void IO::print(std::ostream& output, const std::vector<Edge> & edges){

	for(Edge i : edges){
		output << i.getfrom().getid() << " - " << i.getto().getid() << std::endl;
	}
}
