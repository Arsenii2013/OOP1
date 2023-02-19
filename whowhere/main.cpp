#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "place.hpp"
#include "user.hpp"
#include "database.hpp"
#include "io.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc != 3){
		cout << "Usage:\n ./main place_file log_file" << endl;
		return 0;
	}

	std::ifstream log_file(argv[2]);
	std::ifstream place_file(argv[1]);

	if(!place_file.is_open()){
		cout << "cant open file" << argv[1] << endl;
		return 0;
	}

	if(!log_file.is_open()){
		cout << "cant open file" << argv[2] << endl;
		return 0;
	}

	try{
		PlacesReader pr(place_file);
		LogsReader ur(log_file);

		Database db(ur.get_users(), pr.get_places());

		for(const auto & user: db.get_users()){
			std::ofstream out("User" + std::to_string(user.get_id()) + ".txt");

			if(!out.is_open()){
				cout << "cant open file" << "User" + std::to_string(user.get_id()) + ".txt" << endl;
				return 0;
			}

			LogsWriter lw(out);

			lw.write_entrys(db.get_user_entrys(user.get_id()), db.get_user_path(user.get_id()));

			lw.write_path(db.get_user_path(user.get_id()));
			cout << "file: User" + std::to_string(user.get_id()) + ".txt sucsesfully writed" << endl;
		}
	}catch(const std::invalid_argument & e){
		cout << e.what() << endl;
	}

	return 0;
}
