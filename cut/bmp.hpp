#pragma once
#include "libbitmap.h"
#include <vector>
//#include "bmpmod.hpp"

struct Pixel{ //пиксель
	uint8_t r = 0, g = 0, b = 0;

	Pixel() = default;
	Pixel(uint8_t _r, uint8_t _g, uint8_t _b);

	bool operator==(const Pixel & p);

};

class BMP: public Bitmap{//работа с Bitmap
private:
	size_t m_stride{0};

private:
	void copy(const BMP & _bmp);

public:
	BMP() = default;
	BMP(const BMP & bmp);
	BMP(const std::string & file_name);
	BMP(size_t w, size_t h);
	BMP(const std::vector<std::vector<Pixel>>& arr);

	Pixel get(size_t x, size_t y) const;
	void set(size_t x, size_t y, Pixel p);

	size_t height() const;
	size_t width() const;
	size_t stride() const;
    size_t line_size() const;
    size_t bpp() const { return 3; }

	void operator=(const BMP & _bmp);

	~BMP(void);

};
