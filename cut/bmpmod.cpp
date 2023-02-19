#include "bmpmod.hpp"

#include <cmath>
#include <iostream>
//using namespace std;

BackFinder::BackFinder(std::function<bool(const Pixel&)> _back){
	back = _back;
}

size_t BackFinder::left_edge(const BMP & bmp) const{
	size_t xp = 0;
	for(; xp < bmp.width(); xp++){//сдвигаем полоску с левого края пока все пиксели подходят под фон
		for(size_t y = 0; y < bmp.height(); y++){
			if(!back(bmp.get(xp, y)))
				return xp;
		}
	}
	return xp;
}


size_t BackFinder::right_edge(const BMP & bmp) const{
	size_t xp = bmp.width() - 1;

	for(; xp > 0; xp--){//сдвигаем полоску с левого края пока все пиксели подходят под фон
		for(size_t y = 0; y < bmp.height(); y++){
			if(!back(bmp.get(xp, y)))
				return xp;
		}
	}
	return xp;
}

size_t BackFinder::up_edge(const BMP & bmp) const{
	size_t yp = 0;

	for(; yp < bmp.height(); yp++){//сдвигаем полоску с левого края пока все пиксели подходят под фон
		for(size_t x = 0; x < bmp.width(); x++){
			if(!back(bmp.get(x, yp))){
				//cout<<(int)bmp.get(x, yp).r<<' '<<(int)bmp.get(x, yp).g<<' '<<(int)bmp.get(x, yp).b<<endl;
				return yp;
			}
		}
	}
	return yp;
}


size_t BackFinder::down_edge(const BMP & bmp) const{
	size_t yp = bmp.height() - 1;

	for(; yp > 0; yp--){//сдвигаем полоску с левого края пока все пиксели подходят под фон
		for(size_t x = 0; x < bmp.width(); x++){
			if(!back(bmp.get(x, yp)))
				return yp;
		}
	}
	return yp;
}

BMP BackFinder::cut(const BMP& in){
    auto l = left_edge(in);
    auto u = up_edge(in);
    auto r = right_edge(in);
    auto d = down_edge(in);

    if (l >= r || u >= d)
		throw std::invalid_argument("upper left corner lower or right lower than right corner");

    BMP result{ r - l + 1, d - u + 1 };

    auto srcStride = in.stride();
    auto dstStride = result.stride();
    auto lineSize = result.line_size();

    auto src = in.m_buffer + l * in.bpp() + u * srcStride;
    auto dst = result.m_buffer;

    for (size_t i = 0; i < result.height(); ++i) {
		std::copy(src, src + lineSize, dst);
		src += srcStride;
		dst += dstStride;
    }

    return result;
}

Isback::Isback(const BMP & bmp, float _acc){
	if (bmp.width() == 0 || bmp.height() == 0)
		throw std::invalid_argument("invalid image im isback constructor");
	acc = _acc;

	unsigned int r = 0, g = 0, b = 0;
	for(size_t x = 0; x < bmp.width(); x++){
		auto px = bmp.get(x, 0);
		r += px.r;
		g += px.g;
		b += px.b;
		px = bmp.get(x, bmp.height() - 1);
		r += px.r;
		g += px.g;
		b += px.b;
	}

	for(size_t y = 0; y < bmp.height(); y++){
		auto px = bmp.get(0, y);
		r += px.r;
		g += px.g;
		b += px.b;
		px = bmp.get(bmp.width() - 1, y);
		r += px.r;
		g += px.g;
		b += px.b;
	}
	r = static_cast< unsigned int > (r / (2 * bmp.height() + 2 * bmp.width()));
	g = static_cast< unsigned int > (g / (2 * bmp.height() + 2 * bmp.width()));
	b = static_cast< unsigned int > (b / (2 * bmp.height() + 2 * bmp.width()));
	back_colour = Pixel((uint8_t) r, (uint8_t) g, (uint8_t) b);
}

bool Isback::operator()(const Pixel & px) const{
	auto delta = std::hypot(px.r - back_colour.r, px.g - back_colour.g, px.b - back_colour.b);
    static const auto d = std::hypot(256, 256, 256);
    return delta / d + acc <= 1;
}




