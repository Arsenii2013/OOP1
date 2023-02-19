#include "io.hpp"

#include <iostream>
#include <exception>
#include <filesystem>

Reader::Reader(std::istream & _in): in(_in){
}

std::vector<int>::iterator Reader::read(std::istream_iterator<int> & start, std::istream_iterator<int> stop,
				  	  	  	  	  	  	size_t n, std::vector<int>::iterator dst){

	for(;start != stop && n > 1; ++dst, ++start, --n){
		*dst = *start;
	}

	if(start != stop){
		*dst = *start;
		dst++;
	}
	return dst;
}

int Reader::read(std::vector<int> & arr){
	if(arr.size() == 0)
		throw std::invalid_argument("attempt to read 0 numbers");
	auto it = std::istream_iterator<int>(in);
	auto readed = read(it, std::istream_iterator<int>(),
				       arr.size(), arr.begin());
	return readed - arr.begin();
}
