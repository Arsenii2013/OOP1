#include <iostream>
#include <fstream>

#include "merge.hpp"
#include "io.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc != 4)
		cout << "Usage:\nmain input_file output_file buff_size" << endl;

	try{
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);

		if(!in.is_open() || !out.is_open()){
			cout << "Cant open, or create file" << endl;
		}

		Reader r(in);
		Writer w(out, " ");

		MergeSort ms(r, w, stoi(argv[3]));
		ms.sort();
	}catch(const std::runtime_error & e){
		cout << e.what() << endl;
	}catch(const std::invalid_argument & e){
		cout << e.what() << endl;
	}
	return 0;
}
