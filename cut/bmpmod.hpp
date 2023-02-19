#pragma once
#include "bmp.hpp"
#include <cstdint>
#include <array>
#include <functional>

#define accuracy sqrt(2)

class BackFinder{
private:
	std::function<bool(const Pixel&)> back;
	//Pixel back_color();
public:

	BackFinder(std::function<bool(const Pixel&)> _back);

	size_t left_edge(const BMP & bmp) const;
	size_t right_edge(const BMP & bmp) const;
	size_t up_edge(const BMP & bmp) const;
	size_t down_edge(const BMP & bmp) const;

	BMP cut(const BMP& in);
};

class Isback{//по пикселю определяет фон ли он
private:
	Pixel back_colour;
	float acc = 0;

public:
	Isback(const BMP & bmp, float _acc = 0);

	bool operator()(const Pixel & px) const;

};
