#include "dsu.hpp"
#include <exception>

bool DSU::in_dsu(idt v) const{
	return parent.find(v) != parent.end() && rank.find(v) != rank.end();
}


void DSU::make_set (idt v) {
	parent.insert({v, v});
	rank.insert({v, 0});
}

idt DSU::find_set (idt v) {

	if(!in_dsu(v))
		throw std::out_of_range("node not in DSU");

	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v]);
}

void DSU::union_sets (idt a, idt b) {
	a = find_set (a);
	b = find_set (b);
	if (a != b) {
		if (rank[a] < rank[b])
			std::swap (a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			++rank[a];
	}
}
