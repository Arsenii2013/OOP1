#pragma once
#include <string>

#include "user.hpp"
#include "place.hpp"


class PlacesReader{
private:
	std::istream & in;
public:
	PlacesReader(std::istream & _in);

	std::vector<Place> get_places();
};

class LogsReader{
private:
	std::istream & in;

public:
	LogsReader(std::istream & _in);

	std::vector<User> get_users();
};

class LogsWriter{
private:
	std::ostream & out;

public:
	LogsWriter(std::ostream & _out);

	void write_entrys(const std::vector<UserEntry> & entrys, const std::vector<Place> & places);
	void write_path(const std::vector<Place> & places);
};
