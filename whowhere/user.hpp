#pragma once
#include <vector>

#include "place.hpp"

struct UserEntry{
	time_t ts;
	int x, y;

	bool operator<(const UserEntry & e) const{ return ts < e.ts; }
};

class User{
private:
	std::vector<UserEntry> visited;
	int id{0};

private:
	Place where(const UserEntry & e, const std::vector<Place> & places) const;

public:

	User(int _id, const std::vector<UserEntry> & _visited);

	std::vector<Place> path(const std::vector<Place> & places) const;

	int get_id() const{ return id; }

	const std::vector<UserEntry> & get_entrys() const;

};
