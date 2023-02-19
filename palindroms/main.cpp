#include <iostream>
#include <fstream>
#include <vector>
#include "palindroms.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 2){
		cout << "Error\nType one file name" << endl;
		return 0;
	}

	ifstream file(argv[1]);

	if(!file.is_open()){
		cout << "Error\nIncorrect file name" << endl;
		return 0;
	}

	std::vector<std::string> words = get_phrase(file);

	Phrase ph1(words);
	ph1.words(cout);
	ph1.phrase_as_word(cout);
	ph1.phrase(cout);
	return 0;
}
