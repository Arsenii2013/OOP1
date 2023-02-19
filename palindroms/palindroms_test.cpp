#include "gtest/gtest.h"
#include <string>
#include <vector>

#include "palindroms.hpp"


TEST(Iternal, StrPloy)
{
    EXPECT_EQ('n', Phrase::palindrom(std::string("asd")));
    EXPECT_EQ('y', Phrase::palindrom(std::string("assa")));
    EXPECT_EQ('y', Phrase::palindrom(std::string("a")));
    EXPECT_EQ('y', Phrase::palindrom(std::string("")));
    EXPECT_EQ('y', Phrase::palindrom(std::string("asserttressa")));
}

TEST(Iternal, VectorPloy)
{
	std::vector<std::string> a = {"as", "in", "in", "as"};
	std::vector<std::string> b = {"as", "in", "not", "as"};
	std::vector<std::string> c = {"as"};
	std::vector<std::string> d = {};
    EXPECT_EQ('y', Phrase::palindrom(a));
    EXPECT_EQ('n', Phrase::palindrom(b));
    EXPECT_EQ('y', Phrase::palindrom(c));
    EXPECT_EQ('y', Phrase::palindrom(d));
}
/*
TEST(Iternal, Reverse)
{
	EXPECT_EQ("", reverse(""));
    EXPECT_EQ("fdsa", reverse("asdf"));
    EXPECT_EQ("a", reverse("a"));
}
*/
TEST(GetPhrase, Test1)
{
	std::istringstream is("A nut for a jar of tuna");

	std::vector<std::string> expected = {"a", "nut", "for", "a", "jar", "of", "tuna"};
	EXPECT_EQ(expected, get_phrase(is));
}

TEST(GetPhrase, Test2)
{
	std::istringstream is("there as s as there");

	std::vector<std::string> expected = {"there", "as", "s", "as", "there"};
	EXPECT_EQ(expected, get_phrase(is));
}

TEST(GetPhrase, Test3)
{
	std::istringstream is("A new order began, a more Roman age bred Rowena");

	std::vector<std::string> expected = {"a", "new", "order", "began", "a", "more", "roman", "age", "bred", "rowena"};
	EXPECT_EQ(expected, get_phrase(is));
}


TEST(Word, Test1)
{
	std::ostringstream os;

	std::vector<std::string> in = {"a", "nut", "for", "a", "jar", "of", "tuna"};
	std::string expect = {"Words:\n"
			    			"a - y\n"
							"tun - n\n"
		    				"rof - n\n"
		    				"a - y\n"
		    				"raj - n\n"
		    				"fo - n\n"
		    				"anut - n\n\n"};
	Phrase ph(in);
	ph.words(os);
	EXPECT_EQ(expect, os.str());
}

TEST(Word, Test2)
{
	std::ostringstream os;

	std::vector<std::string> in = {"there", "as", "s", "as", "there"};
	std::string expect = {"Words:\n"
			    			"ereht - n\n"
		    				"sa - n\n"
		    				"s - y\n"
		    				"sa - n\n"
		    				"ereht - n\n\n"};
	Phrase ph(in);
	ph.words(os);
	EXPECT_EQ(expect, os.str());
}

TEST(Word, Test3)
{
	std::ostringstream os;

	std::vector<std::string> in = {"a", "new", "order", "began", "a", "more", "roman", "age", "bred", "rowena"};
	std::string expect = {"Words:\n"
			    			"a - y\n"
		    				"wen - n\n"
							"redro - n\n"
							"nageb - n\n"
							"a - y\n"
							"erom - n\n"
							"namor - n\n"
							"ega - n\n"
							"derb - n\n"
							"anewor - n\n\n"};
	Phrase ph(in);
	ph.words(os);
	EXPECT_EQ(expect, os.str());
}

TEST(PhraseAsWord, Test1)
{
	std::ostringstream os;

	std::vector<std::string> in = {"a", "nut", "for", "a", "jar", "of", "tuna"};
	std::string expect = {"Sentence as a word:\n"
						    "anutforajaroftuna - y\n\n"};
	Phrase ph(in);
	ph.phrase_as_word(os);
	EXPECT_EQ(expect, os.str());
}

TEST(PhraseAsWord, Test2)
{
	std::ostringstream os;

	std::vector<std::string> in = {"there", "as", "s", "as", "there"};
	std::string expect = {"Sentence as a word:\n"
		    				"erehtsassaereht - n\n\n"};
	Phrase ph(in);
	ph.phrase_as_word(os);
	EXPECT_EQ(expect, os.str());
}

TEST(PhraseAsWord, Test3)
{
	std::ostringstream os;

	std::vector<std::string> in = {"a", "new", "order", "began", "a", "more", "roman", "age", "bred", "rowena"};
	std::string expect = {"Sentence as a word:\n"
		    				"aneworderbeganamoreromanagebredrowena - y\n\n"};
	Phrase ph(in);
	ph.phrase_as_word(os);
	EXPECT_EQ(expect, os.str());
}

TEST(Phrase, Test1)
{
	std::ostringstream os;

	std::vector<std::string> in = {"a", "nut", "for", "a", "jar", "of", "tuna"};
	std::string expect = {"Sentence as a word set:\n"
		    				"tuna of jar a for nut a - n\n"};
	Phrase ph(in);
	ph.phrase(os);
	EXPECT_EQ(expect, os.str());
}

TEST(Phrase, Test2)
{
	std::ostringstream os;

	std::vector<std::string> in = {"there", "as", "s", "as", "there"};
	std::string expect = {"Sentence as a word set:\n"
							"there as s as there - y\n"};
	Phrase ph(in);
	ph.phrase(os);
	EXPECT_EQ(expect, os.str());
}

TEST(Phrase, Test3)
{
	std::ostringstream os;

	std::vector<std::string> in = {"a", "new", "order", "began", "a", "more", "roman", "age", "bred", "rowena"};
	std::string expect = {"Sentence as a word set:\n"
		    				"rowena bred age roman more a began order new a - n\n"};
	Phrase ph(in);
	ph.phrase(os);
	EXPECT_EQ(expect, os.str());
}
