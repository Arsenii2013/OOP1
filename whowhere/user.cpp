#include "user.hpp"

#include <algorithm>

User::User(int _id, const std::vector<UserEntry> & _visited){
	id = _id;
	visited = _visited;
	std::sort(visited.begin(), visited.end());
}


Place User::where(const UserEntry & e, const std::vector<Place> & places) const{
	for(const auto & place: places){
		if(place.in(e.x, e.y)){
			return place;
		}
	}
	return Place();
}

std::vector<Place> User::path(const std::vector<Place> & places) const{
	std::vector<Place> res;
	for(const auto & entry: visited){
		res.push_back(where(entry, places));
	}
	return res;
}


const std::vector<UserEntry> & User::get_entrys() const{
	return visited;
}
