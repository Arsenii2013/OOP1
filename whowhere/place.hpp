#pragma once
#include <string>

class Place{
private:
	int l{0}, r{0}, u{0}, d{0};
	std::string name{"unknown place"};
public:
	Place() = default;
	Place(const std::string & _name, int x1, int y1, int x2, int y2);

	bool in(int x, int y)  const;
	const std::string & get_name() const { return name; }
};
