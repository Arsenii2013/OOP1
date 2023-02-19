#include "bmp.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace { // из libbitmap
template < size_t align >
size_t align_size(size_t s)
{
	return ( align & ( align - 1 ) ) ?
		( ( s + align - 1 ) / align ) * align :  // align is not 2 ^ n
		( s + align - 1 ) & ~( align - 1 );        // align is 2 ^ n
}

inline size_t get_line_size(size_t width, size_t bpp)
{
	return align_size < 8 >(width * bpp) >>  3;
}

inline size_t get_stride(size_t width, size_t bpp = 24)
{
	return align_size <  32 >(width * bpp) >>  3;
}

inline size_t get_padding(size_t width, size_t bpp)
{
	return get_stride(width, bpp) - get_line_size(width, bpp);
}

inline size_t get_pixel_array_size(size_t width, size_t height, size_t bpp = 24)
{
	return get_stride(width, bpp) * height;
}
}

Pixel::Pixel(uint8_t _r, uint8_t _g, uint8_t _b){
	r = _r;
	g = _g;
	b = _b;
}

bool Pixel::operator==(const Pixel & p){
	return r == p.r && g == p.g && b == p.b;
}

void BMP::copy(const BMP & _bmp){
	m_stride = get_stride(_bmp.m_width);
	m_height = _bmp.m_height;
	m_width = _bmp.m_width;
	m_buffer = new uint8_t[get_pixel_array_size(m_width, m_height)];
	std::copy(_bmp.m_buffer, _bmp.m_buffer + get_pixel_array_size(m_width, m_height), m_buffer);
}

BMP::BMP(const BMP & _bmp){
	copy(_bmp);
}

void BMP::operator=(const BMP & _bmp){
	clear();
	copy(_bmp);
}


BMP::BMP(size_t w, size_t h){

	m_stride = get_stride(w);

	m_height = h;
	m_width = w;

	if(w != 0 && h != 0)
		m_buffer = new uint8_t[get_pixel_array_size(w, h)];
}

BMP::BMP(const std::string & file_name){
    m_stride = 0;
	if (!load(file_name)) {
		throw std::invalid_argument("can't load '" + file_name + "' file");
	}
	m_stride = get_stride(m_width);
}

BMP::BMP(const std::vector<std::vector<Pixel>>& arr){
	m_width = arr.size();
	m_height = arr[0].size();
	m_stride = get_stride(m_width);
	m_buffer = new uint8_t[get_pixel_array_size(m_width, m_height)];
	for(size_t i = 0; i < arr.size(); i++){
		if(arr[i].size() != m_height)
			throw std::invalid_argument("vector is not rectangular");
		for(size_t j = 0; j < arr[i].size(); j++){
			set(i, j, arr[i][j]);
		}
	}
}

Pixel BMP::get(size_t x, size_t y) const{
	if(x >= m_width)
		throw std::out_of_range("x out of m_width");
	if(y >= m_height)
		throw std::out_of_range("y out of m_height");

	size_t pad = y * m_stride;
	return Pixel(m_buffer[pad + x *  bpp() + 2], m_buffer[pad + x *  bpp() + 1], m_buffer[pad + x *  bpp() + 0]);
}

void BMP::set(size_t x, size_t y, Pixel p){
	if(x >= m_width)
		throw std::out_of_range("x out of m_width");
	if(y >= m_height)
		throw std::out_of_range("y out of m_height");

	size_t pad = y * m_stride;

	m_buffer[pad + x *  bpp() + 2] = p.r;
	m_buffer[pad + x *  bpp() + 1] = p.g;
	m_buffer[pad + x *  bpp() + 0] = p.b;
}

size_t BMP::height() const{
	return m_height;
}

size_t BMP::width() const{
	return m_width;
}

size_t BMP::stride() const{
	return m_stride;
}

size_t BMP::line_size() const
{
	return get_line_size(width(), bpp() * 8);
}
BMP::~BMP(void){
	clear();
}

