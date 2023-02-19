#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "palindroms.hpp"

char Phrase::palindrom(const std::string &str){
	std::string::const_iterator l = str.begin();
	std::string::const_iterator r = str.end();
	if(r == l)
		return 'y';

	while(l <= r){
		r--;
		if(*l == *r){
			l++;
		}else{
			break;
		}

	}

	return l > r ? 'y' : 'n';
}

char Phrase::palindrom(const std::vector<std::string> &strs){
	std::vector<std::string>::const_iterator l = strs.begin();
	std::vector<std::string>::const_iterator r = strs.end();
	if(r == l)
		return 'y';

	while(l <= r){
		r--;
		if(*l == *r){
			l++;

		}else{
			break;
		}

	}

	return l > r ? 'y' : 'n';
}

std::string Phrase::reverse(const std::string &str){
	return std::string(str.rbegin(), str.rend());
}

std::vector<std::string> get_phrase(std::istream& input){
	std::string s;
	std::vector<std::string> words;

	while(input >> s){
		std::transform(s.begin(), s.end(), s.begin(), ::tolower);
		while(s.find('.') != std::string::npos)
			s.erase(s.find('.'), 1);
		while(s.find(',') != std::string::npos)
			s.erase(s.find(','), 1);
		words.push_back(s);
	}
	return words;
}

Phrase::Phrase(const std::vector<std::string> &_word_list){
	word_list = _word_list;
}

void Phrase::words(std::ostream& output){
	output << "Words:" << std::endl;
	for(auto it = word_list.begin(); it != word_list.end(); it++){
		output << reverse(*it) << " - " << palindrom(*it) << std::endl;
	}
	output << std::endl;
}

void Phrase::phrase_as_word(std::ostream& output){
	std::string sum;
	for(auto it = word_list.begin(); it != word_list.end(); it++){
		sum += *it;
	}
	output << "Sentence as a word:" << std::endl;
	output << reverse(sum) << " - " << palindrom(sum) << std::endl << std::endl;
}

void Phrase::phrase(std::ostream& output){
	output << "Sentence as a word set:" << std::endl;
	for(auto it = word_list.rbegin(); it != word_list.rend(); it++)
		output << *it << ' ';
	output << "- " << palindrom(word_list) << std::endl;
}

