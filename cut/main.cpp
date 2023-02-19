#include "libbitmap.h"
#include "bmpmod.hpp"
#include <cmath>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 4){
		cout << "Error\nUsage:\nin_filename out_filename accuracy\n"
				"Accuracy sets the allowable deviation of the color norm in percent" << endl;
		return 0;
	}

	cout << "Input file: " << argv[1] << endl;
	cout << "Output file: " << argv[2] << endl;
	cout << "Accuracy: " << argv[3] << "%" << endl;

    try {
		BMP bmp(argv[1]);
		BackFinder bf(Isback(bmp, std::stof(argv[3]) / 100));
		auto res = bf.cut(bmp);
		res.save(argv[2]);
    }

    catch (const std::exception& e) {
    	cout << e.what() << endl;
    }

	return 0;
}
