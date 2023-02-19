#pragma once
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> get_phrase(std::istream& input);

class Phrase final{
private:
	std::vector<std::string> word_list;
	std::string reverse(const std::string & str);
public:
	Phrase() = default;
	Phrase(const std::vector<std::string> & _word_list);
	~Phrase() = default;

	static char palindrom(const std::string &str);
	static char palindrom(const std::vector<std::string> & strs);


	void words(std::ostream& output);

	void phrase_as_word(std::ostream& output);

	void phrase(std::ostream& output);
};

