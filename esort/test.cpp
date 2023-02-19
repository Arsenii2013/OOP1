#include "gtest/gtest.h"
#include "merge.hpp"
#include "io.hpp"

#include <vector>
#include <exception>

TEST(READER, EMPTY)
{
	{
	std::istringstream is("");
	Reader r(is);
	std::vector<int> a(1);
	EXPECT_EQ(0, r.read(a));
	}

	{
	std::istringstream is("1");
	Reader r(is);
	std::vector<int> a(1);
	EXPECT_EQ(1, r.read(a));
	}

	{
	std::istringstream is("1");
	Reader r(is);
	std::vector<int> a(0);
	EXPECT_THROW(r.read(a), std::invalid_argument);
	}
}

TEST(READER, WRONG)
{
	{
	std::istringstream is("12 dsafa 112 212 jkjfkds 2122");
	Reader r(is);
	std::vector<int> a(1);
	EXPECT_EQ(1, r.read(a));
	}
}

TEST(READER, READ)
{
	{
	std::istringstream is("1 2 3 4 5 6 7 8 9 10");
	Reader r(is);
	std::vector<int> a(10);
	int readed = r.read(a);
	std::vector<int> b(a.begin(), a.begin() + readed);
	EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}), b);
	}

	{
	std::istringstream is("1 2 3 4 5 6 7 8 9 10");
	Reader r(is);
	std::vector<int> a(5);
	int readed = r.read(a);
	std::vector<int> b(a.begin(), a.begin() + readed);
	EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5}), b);
	readed = r.read(a);
	b = std::vector<int>(a.begin(), a.begin() + readed);
	EXPECT_EQ(std::vector<int>({6, 7, 8, 9, 10}), b);
	}
}

TEST(MERGESORT, BAD_CONSTRUCTOR)
{
	std::istringstream is("");
	std::ostringstream os("");
	Reader r(is);
	Writer w(os, " ");
	EXPECT_THROW(MergeSort(r, w, 0), std::invalid_argument);
}

TEST(MERGESORT, EMPTY)
{
	{
	std::istringstream is("");
	std::ostringstream os("");
	Reader r(is);
	Writer w(os, " ");
	MergeSort ms(r, w, 10);

	ms.sort();
	EXPECT_EQ("", os.str());
	}

	{
	std::istringstream is("12");
	std::ostringstream os("");
	Reader r(is);
	Writer w(os, " ");
	MergeSort ms(r, w, 10);

	ms.sort();
	EXPECT_EQ("12 ", os.str());
	}
}

TEST(MERGESORT, TEST1)
{
	{
	std::istringstream is("-3 -2 -1 0 1 2 3");
	std::ostringstream os("");
	Reader r(is);
	Writer w(os, " ");
	MergeSort ms(r, w, 10);

	ms.sort();
	EXPECT_EQ("-3 -2 -1 0 1 2 3 ", os.str());
	}
}

TEST(MERGESORT, TEST2)
{
	{
	std::istringstream is("23 -1 2 566 -6 0 1 3 2 4 -12 33 1234123 211 -1231232");
	std::ostringstream os("");
	Reader r(is);
	Writer w(os, " ");
	MergeSort ms(r, w, 1000);

	ms.sort();
	EXPECT_EQ("-1231232 -12 -6 -1 0 1 2 2 3 4 23 33 211 566 1234123 ", os.str());
	}
}

TEST(MERGESORT, TEST3)
{
	{
	std::istringstream is("-330 -84 -616 -385 638 524 -131 59 -942 246 -720 -605 513 "
			"614 55 -298 -541 -833 497 978 676 129 626 -280 954 910 549 -127 -189 -383 "
			"-530 574 -747 688 884 -962 653 -673 -411 165 328 327 -273 -78 -500 691 "
			"-1000 -128 -779 603 -775 -190 856 -343 661 310 -822 -887 475 208 214 221 "
			"-832 -20 132 765 -183 -598 75 667 670 155 133 669 -755 -91 763 -909 -249 "
			"-606 -120 237 929 -472 -991 621 509 -765 -337 816 -392 -919 -35 552 -136 "
			"-15 -696 -848 -342 443");
	std::ostringstream os("");
	Reader r(is);
	Writer w(os, " ");
	MergeSort ms(r, w, 10);

	ms.sort();
	EXPECT_EQ("-1000 -991 -962 -942 -919 -909 -887 -848 -833 -832 -822 -779 -775 -765 "
			"-755 -747 -720 -696 -673 -616 -606 -605 -598 -541 -530 -500 -472 -411 -392 "
			"-385 -383 -343 -342 -337 -330 -298 -280 -273 -249 -190 -189 -183 -136 -131 "
			"-128 -127 -120 -91 -84 -78 -35 -20 -15 55 59 75 129 132 133 155 165 208 214 "
			"221 237 246 310 327 328 443 475 497 509 513 524 549 552 574 603 614 621 626 "
			"638 653 661 667 669 670 676 688 691 763 765 816 856 884 910 929 954 978 "
			, os.str());
	}
}

TEST(MERGESORT, TEST4)
{
	{
	std::istringstream is("659 846 16 -555 -642 -687 738 47 -599 470 740 845 -285 605 "
			"-667 -434 -821 717 -97 303 -887 -805 -424 -169 162 852 -695 -446 -270 655 "
			"-533 42 12 -108 958 -224 -968 152 -632 -219 528 19 863 -494 -831 -656 940 "
			"-628 -310 -567 -164 -679 384 -765 -229 -737 432 -57 -429 565 -102 748 943 "
			"646 512 -319 -897 -486 13 -579 430 546 -571 -325 30 161 254 -910 -317 -902 "
			"631 914 553 -83 -796 319 -12 721 -914 -754 103 157 -287 -309 70 -335 -904 "
			"506 110 -133 ");
	std::ostringstream os("");
	Reader r(is);
	Writer w(os, " ");
	MergeSort ms(r, w, 1);

	ms.sort();
	EXPECT_EQ("-968 -914 -910 -904 -902 -897 -887 -831 -821 -805 -796 -765 -754 -737 "
			"-695 -687 -679 -667 -656 -642 -632 -628 -599 -579 -571 -567 -555 -533 "
			"-494 -486 -446 -434 -429 -424 -335 -325 -319 -317 -310 -309 -287 -285 "
			"-270 -229 -224 -219 -169 -164 -133 -108 -102 -97 -83 -57 -12 12 13 16 "
			"19 30 42 47 70 103 110 152 157 161 162 254 303 319 384 430 432 470 506 "
			"512 528 546 553 565 605 631 646 655 659 717 721 738 740 748 845 846 852 "
			"863 914 940 943 958 ", os.str());
	}
}
