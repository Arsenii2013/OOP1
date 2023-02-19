#include "io.hpp"

#include <map>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <chrono>
#include <locale>
#include <iomanip>
#include <time.h>
#include <sys/time.h>

#define dateTimeFormat "%Y-%m-%dT%H:%M:%S"

PlacesReader::PlacesReader(std::istream & _in): in(_in){
}

std::vector<Place> PlacesReader::get_places(){
	std::string s;
	std::vector<Place> res;

	while(getline(in, s)){
		std::string name;
		int x1, x2, y1, y2;

		std::istringstream iss(s);

		if (!(iss >> name >> x1 >> y1 >> x2 >> y2))
			throw std::runtime_error(s);
		res.push_back({name, x1, y1, x2, y2});
	}
	return res;
}

LogsReader::LogsReader(std::istream & _in): in(_in){
}

namespace {
    time_t parse_time(std::string time) {
        std::istringstream ss{time};
        std::tm dt{};

        if (!(ss >> std::get_time(&dt, dateTimeFormat)) || ss.fail())
            throw std::invalid_argument("wrong time format");

        return std::mktime(&dt);
    }
}

std::vector<User> LogsReader::get_users(){
	std::map<int, std::vector<UserEntry>> res;

	std::string s;
	while(getline(in, s)){
		time_t ts;
		int id;
		int x, y;
		std::string timestr;

		std::istringstream iss(s);

		if (!(iss >> timestr >> id >> x >> y))
			throw std::runtime_error(s);

		ts = parse_time(timestr);

		auto user = res.find(id);
		if(user == res.end())
			res.insert({id, std::vector<UserEntry>({{ts, x, y}})});
		else
			user->second.push_back({ts, x, y});
	}

	std::vector<User> toret;

	for(const auto & entry: res){
		toret.push_back({entry.first, entry.second});
	}

	return toret;
}

LogsWriter::LogsWriter(std::ostream & _out): out(_out){

}

void LogsWriter::write_entrys(const std::vector<UserEntry> & entrys, const std::vector<Place> & places){
	if(entrys.size() != places.size())
		throw std::invalid_argument("sizes must be equal");

	struct tm buf;
	for(int i = 0; i < entrys.size(); i++)
		out << std::put_time(::localtime_r(&(entrys[i].ts), &buf), dateTimeFormat) << ' ' << entrys[i].x << ' ' <<
		entrys[i].y << ' ' << places[i].get_name() << std::endl;
}

void LogsWriter::write_path(const std::vector<Place> & places){
	out << places[0].get_name();
	for(int i = 1; i < places.size(); i++){
		if(places[i].get_name() != places[i - 1].get_name())
			out << " - " << places[i].get_name();
	}
	out << std::endl;
}

