#include <stdexcept>

#include "database.hpp"

Database::Database(const std::vector<User> & _users, const std::vector<Place> & _places){
	users = _users;
	places = _places;
}
const std::vector<User> & Database::get_users() const{
	return users;
}

const std::vector<UserEntry> & Database::get_user_entrys(int user_id) const{
	for(const auto & user: users){
		if(user.get_id() == user_id)
			return user.get_entrys();
	}
	throw std::invalid_argument("user id not in database");
}

std::vector<Place> Database::get_user_path(int user_id) const{
	for(const auto & user: users){
		if(user.get_id() == user_id)
			return user.path(places);
	}

	throw std::invalid_argument("user id not in database");
}
