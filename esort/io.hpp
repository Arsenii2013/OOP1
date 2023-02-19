#pragma once
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

class Reader{
private:
	std::istream & in;

private:
	std::vector<int>::iterator  read(std::istream_iterator<int> & start, std::istream_iterator<int> stop,
									 size_t n, std::vector<int>::iterator  dst);
public:
	Reader(std::istream & _in);
	int read(std::vector<int> & arr);
};

typedef std::ostream_iterator<int,
		std::ostream_iterator<int>::char_type,
		std::ostream_iterator<int>::traits_type>
		Writer;
