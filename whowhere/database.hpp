#pragma once
#include "user.hpp"
#include "place.hpp"

class Database{
private:
	std::vector<Place> places;
	std::vector<User> users;

public:
	Database(const std::vector<User> & _users, const std::vector<Place> & _places);

	const std::vector<User> & get_users() const;

	const std::vector<UserEntry> & get_user_entrys(int user_id) const;
	std::vector<Place> get_user_path(int user_id) const;
};
