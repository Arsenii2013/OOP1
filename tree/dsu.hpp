#pragma once

#include <map>

#include "edge.hpp"
class DSU final{
private:
	std::map<idt, idt> parent;
	std::map<idt, int> rank;
public:
	bool in_dsu(idt v) const;
	void make_set(idt v);
	idt find_set (idt v) ;
	void union_sets (idt a, idt b);
};
