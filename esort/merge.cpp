#include "merge.hpp"
#include "io.hpp"

#include <iostream>
#include <exception>
#include <filesystem>

namespace{
	typedef std::ostream_iterator<int,
			std::ostream_iterator<int>::char_type,
			std::ostream_iterator<int>::traits_type>
			nice_ostream_iterator;
}


MergeSort::MergeSort(Reader & _r, Writer & _w, size_t buff_size): r(_r), w(_w), ram_size(buff_size){
	if(buff_size == 0)
		throw std::invalid_argument("ram size cant be eqval 0");
}


namespace{
	typedef std::ostream_iterator<int,
			std::ostream_iterator<int>::char_type,
			std::ostream_iterator<int>::traits_type>
			nice_ostream_iterator;
}

void MergeSort::sort(){
	std::vector<int> ram(ram_size);

	std::string curr = "file name that the user will never write 1";
	std::string next = "file name that the user will never write 2";

	{//создание/очистка файлов
		std::ofstream f1(next);
		std::ofstream f2(curr);
	}
	size_t readed = 0;
	while((readed = r.read(ram))){

		std::sort(ram.begin(), ram.begin() + readed);

		std::ifstream curr_file(curr);
		std::ofstream next_file(next);

		std::merge(ram.begin(), ram.begin() + readed, std::istream_iterator<int>(curr_file), std::istream_iterator<int>(),
				   nice_ostream_iterator(next_file, " "));

		std::swap(curr, next);
	}

	{//переносим в выходной файл
		std::ifstream curr_file(curr);

		std::copy(std::istream_iterator<int>(curr_file), std::istream_iterator<int>(), w);
	}

	{//
		std::filesystem::remove(curr);
		std::filesystem::remove(next);
	}
}
