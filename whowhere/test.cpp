#include "gtest/gtest.h"

#include "place.hpp"
#include "user.hpp"
#include "database.hpp"
#include "io.hpp"

#include <sstream>

TEST(Place, In){
	{
	Place p("test", 0, 0, 100, 100);

	EXPECT_EQ("test", p.get_name());

	EXPECT_TRUE(p.in(50, 50));
	EXPECT_TRUE(p.in(0, 0));
	EXPECT_TRUE(p.in(100, 100));
	EXPECT_FALSE(p.in(-100, -100));
	}

	{
	auto p = Place();

	EXPECT_EQ("unknown place", p.get_name());

	EXPECT_TRUE(p.in(0, 0));
	EXPECT_FALSE(p.in(100, 100));
	EXPECT_FALSE(p.in(-100, -100));
	}
}

bool operator==(const Place & p1, const Place & p2){
	return p1.get_name() == p2.get_name();
}

bool operator==(const UserEntry & e1, const UserEntry & e2){
	return !(e2 < e1 || e1 < e2);
}

TEST(User, Empty){
	{
	User u(1, std::vector<UserEntry>({}));

	EXPECT_EQ(std::vector<Place>(), u.path(std::vector<Place>()));
	EXPECT_EQ(std::vector<UserEntry>(), u.get_entrys());
	}
}

TEST(User, PathEntrys1){
	{
	const std::vector<Place> places({});

	User u(1, std::vector<UserEntry>({{100, 0, 0}, {200, 23, 23}, {50, 4, 4}, {10000000, 123, 123}}));

	EXPECT_EQ(1, u.get_id());

	const std::vector<UserEntry> expect({{50, 4, 4}, {100, 0, 0}, {200, 23, 23}, {10000000, 123, 123}});

	EXPECT_EQ(expect, u.get_entrys());

	const std::vector<Place> eplaces({Place(), Place(), Place(), Place()});

	EXPECT_EQ(eplaces, u.path(std::vector<Place>()));
	}

	{
	const std::vector<Place> places({{"test1", 0, 0, 100, 100}});

	User u(1, std::vector<UserEntry>({{100, 0, 0}, {200, 23, 23}, {50, 4, 4}, {10000000, 123, 123}}));

	EXPECT_EQ(1, u.get_id());

	const std::vector<UserEntry> expect({{50, 4, 4}, {100, 0, 0}, {200, 23, 23}, {10000000, 123, 123}});

	EXPECT_EQ(expect, u.get_entrys());

	const std::vector<Place> eplaces({{"test1", 0, 0, 100, 100}, {"test1", 0, 0, 100, 100},
									  {"test1", 0, 0, 100, 100}, Place()});

	EXPECT_EQ(eplaces, u.path(places));
	}
}

TEST(User, PathEntrys2){
	{
	const std::vector<Place> places({{"test1", 0, 0, 100, 100}, {"test2", 101, 101, 200, 200},
									 {"test3", -1, -1, -100, -100}, {"test4", -101, -101, -200, -200}});

	User u(1, std::vector<UserEntry>({{100, 0, 0}, {200, 23, 23}, {50, -4, -4},
								  {300, 123, 123}, {0, -190, -190}}));

	EXPECT_EQ(1, u.get_id());

	const std::vector<UserEntry> expect({{0, -130, -130}, {50, -4, -4}, {100, 0, 0},
									 {200, 23, 23}, {300, 123, 123}});

	EXPECT_EQ(expect, u.get_entrys());

	const std::vector<Place> eplaces({{"test4", -101, -101, -200, -200}, {"test3", -1, -1, -100, -100},
									  {"test1", 0, 0, 100, 100}, {"test1", 0, 0, 100, 100},
									  {"test2", 101, 101, 200, 200}});

	EXPECT_EQ(eplaces, u.path(places));
	}
}


TEST(Database, Wrong){
	{
	std::vector<User> users({{1, std::vector<UserEntry>()}, {2, std::vector<UserEntry>()}});

	Database db(users, std::vector<Place>());
	EXPECT_THROW(db.get_user_entrys(10), std::invalid_argument);
	EXPECT_THROW(db.get_user_path(10), std::invalid_argument);
	}
}


TEST(Database, TestEmptyPlaces){
	{
	std::vector<UserEntry> entrys1({{100, 0, 0}, {200, 23, 23}, {50, 4, 4}, {10000000, 123, 123}});
	std::vector<UserEntry> entrys2({{100, 1, 1}, {200, 34, 34}, {140, 4, 4}, {10000, 123, 123}});

	std::vector<User> users({{1, entrys1}, {2, entrys2}});

	Database db(users, std::vector<Place>());

	EXPECT_EQ(std::vector<UserEntry> ({{50, 4, 4}, {100, 0, 0}, {200, 23, 23}, {10000000, 123, 123}}),
				db.get_users()[0].get_entrys());
	EXPECT_EQ(std::vector<UserEntry> ({{100, 1, 1}, {140, 4, 4}, {200, 34, 34}, {10000, 123, 123}}),
				db.get_users()[1].get_entrys());

	EXPECT_EQ(std::vector<UserEntry> ({{50, 4, 4}, {100, 0, 0}, {200, 23, 23}, {10000000, 123, 123}}),
				db.get_user_entrys(1));
	EXPECT_EQ(std::vector<UserEntry> ({{100, 1, 1}, {140, 4, 4}, {200, 34, 34}, {10000, 123, 123}}),
				db.get_user_entrys(2));

	EXPECT_EQ(std::vector<Place>({Place(), Place(), Place(), Place()}), db.get_user_path(1));
	EXPECT_EQ(std::vector<Place>({Place(), Place(), Place(), Place()}), db.get_user_path(2));
	}
}

TEST(Database, General){
	{
	std::vector<UserEntry> entrys1({{100, 0, 0}, {200, 23, 23}, {50, 4, 4}, {10000000, 123, 123}});
	std::vector<UserEntry> entrys2({{100, 1, 1}, {200, 34, 34}, {140, 4, 4}, {10000, 123, 123}});

	std::vector<User> users({{1, entrys1}, {2, entrys2}});

	Database db(users, std::vector<Place>({{"test", 0, 0, 23, 23}}));

	EXPECT_EQ(std::vector<Place>({{"test", 0, 0, 23, 23}, {"test", 0, 0, 23, 23},
											  {"test", 0, 0, 23, 23}, Place()}), db.get_user_path(1));
	EXPECT_EQ(std::vector<Place>({{"test", 0, 0, 23, 23}, {"test", 0, 0, 23, 23},
											   Place(), Place()}), db.get_user_path(2));
	}
}

TEST(IO, PlacesReader1){
	{
	std::istringstream in("test1 0 0 100 100\n"
						  "test2 123 123 200 200\n"
						  "test3 56 56 76 76");
	const std::vector<Place> places({{"test1", 0, 0, 100, 100}, {"test2", 123, 123, 200, 200},
									 {"test3", 56, 56, 76, 76}});

	PlacesReader pr(in);

	EXPECT_EQ(places, pr.get_places());
	}
}

TEST(IO, PlacesReaderWrong){
	{
	std::istringstream in("test1 0  100 100\n"
						  "test2 123 123 200 200\n"
						  "test3 56 56 76 76");
	const std::vector<Place> places({{"test1", 0, 0, 100, 100}, {"test2", 123, 123, 200, 200},
									 {"test3", 56, 56, 76, 76}});

	PlacesReader pr(in);

	EXPECT_THROW(pr.get_places(), std::runtime_error);
	}

	{
	std::istringstream in("test1 0 ttt 100 100\n"
						  "test2 123 123 200 200\n"
						  "test3 56 56 76 76");
	const std::vector<Place> places({{"test1", 0, 0, 100, 100}, {"test2", 123, 123, 200, 200},
									 {"test3", 56, 56, 76, 76}});

	PlacesReader pr(in);

	EXPECT_THROW(pr.get_places(), std::runtime_error);
	}
}

TEST(IO, LogsReader){
	{
	std::istringstream in("1970-01-01T07:01:40 1 0 100\n"
						  "1970-01-01T07:03:20 2 123 200\n"
						  "1970-01-01T07:00:00 1 56 76\n"
						  "1970-01-01T07:00:00 2 0 0");

	LogsReader lr(in);

	auto users = lr.get_users();

	EXPECT_EQ(1, users[0].get_id());
	EXPECT_EQ(2, users[1].get_id());

	EXPECT_EQ(std::vector<UserEntry> ({{0, 56, 76}, {100, 0, 100}}), users[0].get_entrys());
	EXPECT_EQ(std::vector<UserEntry> ({{0, 0, 0}, {200, 123, 200}}), users[1].get_entrys());
	}
}

TEST(IO, LogsReaderWrong){
	{
	std::istringstream in("1970-01-01T07:01:40 1 df 100\n"
						  "1970-01-01T07:03:20 2 123 200\n"
						  "1970-01-01T07:00:00 1 56 76\n"
						  "1970-01-01T07:00:00 2 0 0");

	LogsReader lr(in);

	EXPECT_THROW(lr.get_users(), std::runtime_error);
	}
}

TEST(IO, LogsWriter){
	{
	std::ostringstream out;
	LogsWriter lw(out);

	const std::vector<UserEntry> entrys({{0, -130, -130}, {50, -4, -4}, {100, 0, 0},
									 {200, 23, 23}, {300, 123, 123}});

	const std::vector<Place> places({{"test4", -101, -101, -200, -200}, {"test3", -1, -1, -100, -100},
									 {"test1", 0, 0, 100, 100}, {"test1", 0, 0, 100, 100},
									 {"test2", 101, 101, 200, 200}});

	lw.write_entrys(entrys, places);
	lw.write_path(places);

	EXPECT_EQ("1970-01-01T07:00:00 -130 -130 test4\n"
			  "1970-01-01T07:00:50 -4 -4 test3\n"
			  "1970-01-01T07:01:40 0 0 test1\n"
			  "1970-01-01T07:03:20 23 23 test1\n"
			  "1970-01-01T07:05:00 123 123 test2\n"
			  "test4 - test3 - test1 - test2\n", out.str());
	}
}

