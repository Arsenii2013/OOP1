#include "gtest/gtest.h"
#include <stdexcept>

#include "bmp.hpp"
#include "bmpmod.hpp"

#define white Pixel(255, 255, 255)
#define black Pixel(0, 0, 0)
#define gray Pixel(127, 127, 127)
#define gray_black Pixel(254, 254, 254)

BMP white100x100(){
	std::vector<std::vector<Pixel>> arr;

	for(size_t i = 0; i < 100; i++){
		arr.push_back(std::vector<Pixel>());
		for(size_t j = 0; j < 100; j++)
			arr[i].push_back(white);
	}

	return arr;
}

BMP blackandwhite100x100(){
	std::vector<std::vector<Pixel>> arr;

	for(size_t i = 0; i < 100; i++){
		arr.push_back(std::vector<Pixel>());
		for(size_t j = 0; j < 100; j++)
			arr[i].push_back(white);
	}

	for(size_t i = 0; i < 50; i++){
		for(size_t j = 0; j < 100; j++)
			arr[i][j] = black;
	}
	for(size_t i = 0; i < 100; i++){
		for(size_t j = 0; j < 50; j++)
			arr[i][j] = black;
	}

	for(size_t i = 75; i < 100; i++){
		for(size_t j = 75; j < 100; j++)
			arr[i][j] = black;
	}

	return arr;
}

BMP eblackandwhite100x100(){
	std::vector<std::vector<Pixel>> arr;

	for(size_t i = 0; i < 50; i++){
		arr.push_back(std::vector<Pixel>());
		for(size_t j = 0; j < 50; j++)
			arr[i].push_back(white);
	}

	for(size_t i = 25; i < 50; i++){
		for(size_t j = 25; j < 50; j++)
			arr[i][j] = black;
	}

	return arr;
}

BMP gradient(){
	std::vector<std::vector<Pixel>> arr =
	{std::vector<Pixel>{black, black,     	    black,     	    black,     	    black,          black},
	std::vector<Pixel>{black, Pixel(1, 1, 1), Pixel(1, 1, 1), Pixel(1, 1, 1), Pixel(1, 1, 1), black},
	std::vector<Pixel>{black, Pixel(1, 1, 1), Pixel(9, 9, 9), Pixel(9, 9, 9), Pixel(1, 1, 1), black},
	std::vector<Pixel>{black, Pixel(1, 1, 1), Pixel(9, 9, 9), Pixel(9, 9, 9), Pixel(1, 1, 1), black},
	std::vector<Pixel>{black, Pixel(1, 1, 1), Pixel(1, 1, 1), Pixel(1, 1, 1), Pixel(1, 1, 1), black},
	std::vector<Pixel>{black, black,     	    black,     	    black,     	    black,          black}};
	return arr;
}

BMP e1gradient(){
	std::vector<std::vector<Pixel>> arr =
	{
	std::vector<Pixel>{Pixel(1, 1, 1), Pixel(1, 1, 1), Pixel(1, 1, 1), Pixel(1, 1, 1)},
	std::vector<Pixel>{Pixel(1, 1, 1), Pixel(9, 9, 9), Pixel(9, 9, 9), Pixel(1, 1, 1)},
	std::vector<Pixel>{Pixel(1, 1, 1), Pixel(9, 9, 9), Pixel(9, 9, 9), Pixel(1, 1, 1)},
	std::vector<Pixel>{Pixel(1, 1, 1), Pixel(1, 1, 1), Pixel(1, 1, 1), Pixel(1, 1, 1)}};
	return arr;
}

BMP e2gradient(){
	std::vector<std::vector<Pixel>> arr =
	{
	std::vector<Pixel>{Pixel(9, 9, 9), Pixel(9, 9, 9)},
	std::vector<Pixel>{Pixel(9, 9, 9), Pixel(9, 9, 9)}};
	return arr;
}


//генерировать все картинки

TEST(BMP, SetGet){
	{
	BMP bmp2(150, 150);

	EXPECT_EQ(150, bmp2.height());
	EXPECT_EQ(150, bmp2.width());
	//EXPECT_EQ(256 * 3, bmp2.stride());

	for(size_t i = 0; i < bmp2.width(); i++)
		for(size_t j = 0; j < bmp2.height(); j++)
			bmp2.set(i, j, {123, 23, 12});

	EXPECT_TRUE(Pixel(123, 23, 12) == bmp2.get(0, 0));
	EXPECT_TRUE(Pixel(123, 23, 12) == bmp2.get(149, 149));
	}


	{
	const BMP bmp1 = white100x100();
	EXPECT_EQ(100, bmp1.height());
	EXPECT_EQ(100, bmp1.width());
	//EXPECT_EQ(128 * 3, bmp1.stride());

	EXPECT_TRUE(Pixel(255, 255, 255) == bmp1.get(0, 0));
	EXPECT_TRUE(Pixel(255, 255, 255) == bmp1.get(99, 99));
	}

}


TEST(BMP, Copy){
	{
	BMP bmp1(150, 150);

	for(size_t i = 0; i < bmp1.width(); i++)
		for(size_t j = 0; j < bmp1.height(); j++)
			bmp1.set(i, j, {123, 23, 12});

	BMP bmp2(bmp1);

	EXPECT_EQ(150, bmp2.height());
	EXPECT_EQ(150, bmp2.width());
	//EXPECT_EQ(256 * 3, bmp2.stride());

	EXPECT_TRUE(Pixel(123, 23, 12) == bmp2.get(0, 0));
	EXPECT_TRUE(Pixel(123, 23, 12) == bmp2.get(149, 149));
	}


	{
	const BMP bmp = white100x100();

	BMP bmp1;
	bmp1 = bmp;
	EXPECT_EQ(100, bmp1.height());
	EXPECT_EQ(100, bmp1.width());
	//EXPECT_EQ(128 * 3, bmp1.stride());

	EXPECT_TRUE(Pixel(255, 255, 255) == bmp1.get(0, 0));
	EXPECT_TRUE(Pixel(255, 255, 255) == bmp1.get(99, 99));
	}

}

TEST(BMP, OutOfRange){
	BMP bmp(150, 150);

	EXPECT_THROW(bmp.get(151, 0), std::out_of_range);
	EXPECT_THROW(bmp.get(0, 151), std::out_of_range);

	EXPECT_THROW(bmp.set(151, 0, Pixel(123, 23, 12)), std::out_of_range);
	EXPECT_THROW(bmp.set(0, 151, Pixel(123, 23, 12)), std::out_of_range);
}

TEST(Isback, Isback){
	{
	BMP bmp1 = white100x100();

	Isback is1(bmp1, 1);

	EXPECT_TRUE(is1(bmp1.get(49, 49)));
	EXPECT_TRUE(is1(bmp1.get(0, 0)));
	EXPECT_TRUE(is1(bmp1.get(99, 99)));
	}

	{
	BMP bmp2 = blackandwhite100x100();

	Isback is2(bmp2, 1);

	EXPECT_FALSE(is2(bmp2.get(49, 49)));
	EXPECT_FALSE(is2(bmp2.get(0, 0)));
	EXPECT_FALSE(is2(bmp2.get(99, 99)));

	Isback is3(bmp2, 0);

	EXPECT_TRUE(is3(bmp2.get(49, 49)));
	EXPECT_TRUE(is3(bmp2.get(0, 0)));
	EXPECT_TRUE(is3(bmp2.get(99, 99)));
	}
}

TEST(BackFinder, Edges){
	BMP bmp1 = blackandwhite100x100();

	{
	Isback is1(bmp1, 1);
	BackFinder bf1(is1);

	EXPECT_EQ(0, bf1.up_edge(bmp1));
	EXPECT_EQ(99, bf1.down_edge(bmp1));
	EXPECT_EQ(0, bf1.left_edge(bmp1));
	EXPECT_EQ(99, bf1.right_edge(bmp1));
	}

	{
	Isback is2(bmp1, 0.8);
	BackFinder bf2(is2);
	EXPECT_EQ(50, bf2.up_edge(bmp1));
	EXPECT_EQ(99, bf2.down_edge(bmp1));
	EXPECT_EQ(50, bf2.left_edge(bmp1));
	EXPECT_EQ(99, bf2.right_edge(bmp1));
	}
}

bool bmp_eq(const BMP & bmp1, const BMP & bmp2){
	for(size_t i = 0; i < bmp1.width(); i++)
		for(size_t j = 0; j < bmp1.height(); j++)
			if(!(bmp1.get(i, j) == bmp2.get(i, j)))
				return false;
	return true;
}

TEST(BackFinder, Cut1){
	const BMP expected = eblackandwhite100x100();
	BMP bmp1 = blackandwhite100x100();

	Isback is1(bmp1, 0.8);
	BackFinder bf1(is1);
	bmp1 = bf1.cut(bmp1);

	EXPECT_EQ(expected.height(), bmp1.height());
	EXPECT_EQ(expected.width(), bmp1.width());

	EXPECT_TRUE(bmp_eq(expected, bmp1));

}

TEST(BackFinder, Cut2){
	{
	BMP bmp1 = gradient();
	const BMP blur0 = e1gradient();

	Isback is0(bmp1, 1);
	BackFinder bf0(is0);
	BMP bmp0(bf0.cut(bmp1));

	EXPECT_EQ(blur0.height(), bmp0.height());
	EXPECT_EQ(blur0.width(), bmp0.width());

	EXPECT_TRUE(bmp_eq(blur0, bmp0));
	}

	{
	BMP bmp1 = gradient();

	const BMP blur4 = e2gradient();

	Isback is0(bmp1, 0.98);
	BackFinder bf0(is0);
	BMP bmp0(bf0.cut(bmp1));

	EXPECT_EQ(blur4.height(), bmp0.height());
	EXPECT_EQ(blur4.width(), bmp0.width());

	EXPECT_TRUE(bmp_eq(blur4, bmp0));
	}

}

TEST(BackFinder, Cut3){
	BMP bmp1 = white100x100();

	Isback is0(bmp1, 0.9);
	BackFinder bf0(is0);

	EXPECT_THROW(bf0.cut(bmp1), std::invalid_argument);

}
