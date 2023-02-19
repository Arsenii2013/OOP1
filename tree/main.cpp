#include <fstream>
#include <iostream>

#include "graph.hpp"
#include "io.hpp"

using namespace std;

int main(int argc, char ** argv) {
	if(argc != 2){
		cout << "Error\nType one file name" << endl;
		return 0;
	}

	ifstream file(argv[1]);

	if(!file.is_open()){
		cout << "Error\nIncorrect file name" << endl;
		return 0;
	}

	try{
		vector<Point> points;

		points = IO::parse(file);

		Graph igraph(points);
			Graph ograph = igraph.kruskal();

			auto edges = ograph.get_edges();
			IO::print(cout, edges);
	}catch(const std::runtime_error & e){
		cout << "Invalid string \"" << e.what() << "\"" << endl;
	}catch(const std::out_of_range & e){
		cout << "DSU error:" << e.what() << endl;
	}catch(const std::invalid_argument & e){
		cout << "Edge construction error" << e.what() << endl;
	}
	return 0;
}
