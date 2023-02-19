#pragma once
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#include "io.hpp"

class MergeSort{
private:
	Reader & r;
	Writer & w;
	size_t ram_size{0};

public:

	MergeSort(Reader & _r, Writer & _w, size_t buff_size);

	void sort(const std::string & in, const std::string & out);

	void sort();
};
