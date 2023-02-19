#include <algorithm>

#include "graph.hpp"
#include "dsu.hpp"

Graph::Graph(const std::vector<Edge> & _edges){
	edges = _edges;
}

Graph::Graph(const std::vector<Point> & pts){
	for(auto i = pts.begin(); i != pts.end(); i++)
		for(auto j = i + 1; j != pts.end(); j++)
			edges.push_back(Edge(*i, *j));
}

Graph Graph::kruskal() const{
	DSU dsu;
	for(auto i: edges){
		if(!dsu.in_dsu(i.getfrom().getid()))
			dsu.make_set(i.getfrom().getid());
		if(!dsu.in_dsu(i.getto().getid()))
			dsu.make_set(i.getto().getid());
	}

	std::vector<Edge> ograph;

	std::vector<Edge> sorted = edges;
	sort(sorted.begin(), sorted.end());
	for(auto i : sorted){
		if(dsu.find_set(i.getto().getid()) != dsu.find_set(i.getfrom().getid())){
			dsu.union_sets(i.getfrom().getid(), i.getto().getid());
			ograph.push_back(i);
		}
	}
	return ograph;
}


const std::vector<Edge> & Graph::get_edges() const{
	return edges;
}
