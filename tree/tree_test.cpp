#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include "dsu.hpp"
#include "point.hpp"
#include "edge.hpp"
#include "graph.hpp"
#include "io.hpp"

#define err (1e-7)

TEST(DSU, in_dsu)
{
	DSU dsu;
	dsu.make_set(5);
	EXPECT_TRUE(dsu.in_dsu(5));
	EXPECT_FALSE(dsu.in_dsu(1));

	const DSU dsu1 = dsu;
	EXPECT_FALSE(dsu.in_dsu(3));
}

TEST(DSU, find_set)
{
	DSU dsu;
	dsu.make_set(5);
	dsu.make_set(3);
	dsu.make_set(1);

	EXPECT_EQ(1, dsu.find_set(1));
	EXPECT_EQ(3, dsu.find_set(3));

	EXPECT_THROW(dsu.find_set(8), std::out_of_range);
}

TEST(DSU, union_sets)
{
	DSU dsu;
	dsu.make_set(5);
	dsu.make_set(3);
	dsu.make_set(1);
	dsu.union_sets(1, 3);

	EXPECT_THROW(dsu.union_sets(1, 7), std::out_of_range);

	EXPECT_EQ(dsu.find_set(3), dsu.find_set(1));
	EXPECT_TRUE(dsu.find_set(1) == 3 || dsu.find_set(1) == 1);
	EXPECT_NE(dsu.find_set(5), dsu.find_set(1));
}

TEST(DSU, Unit)
{
	DSU dsu;
	dsu.make_set(5);
	dsu.make_set(3);
	dsu.make_set(1);
	dsu.make_set(2);
	dsu.make_set(4);

	dsu.union_sets(1, 3);

	EXPECT_EQ(dsu.find_set(3), dsu.find_set(1));
	EXPECT_NE(dsu.find_set(5), dsu.find_set(1));
	EXPECT_NE(dsu.find_set(2), dsu.find_set(4));
	EXPECT_FALSE(dsu.in_dsu(76));
	EXPECT_TRUE(dsu.in_dsu(2));
	EXPECT_TRUE(dsu.in_dsu(1));

	dsu.union_sets(1, 5);
	dsu.union_sets(3, 4);

	EXPECT_TRUE((dsu.find_set(3) == dsu.find_set(4)) && (dsu.find_set(1) == dsu.find_set(5))
			&& (dsu.find_set(1) == dsu.find_set(4)));

	EXPECT_NE(dsu.find_set(2), dsu.find_set(4));
	EXPECT_FALSE(dsu.in_dsu(76));
	EXPECT_TRUE(dsu.in_dsu(5));
	EXPECT_TRUE(dsu.in_dsu(3));
}


TEST(Point, Get)
{
	{
	const Point a(1, 2, 3.5);

	EXPECT_EQ(1, a.getid());
	EXPECT_EQ(2, a.getx());
	EXPECT_EQ(3.5, a.gety());
	}

	{
	Point a(1, 2, 3.5);

	EXPECT_EQ(1, a.getid());
	EXPECT_EQ(2, a.getx());
	EXPECT_EQ(3.5, a.gety());
	}
}

TEST(Point, EQ)
{
	const Point a(1, 2, 3);
	{
	Point c(1, 2, 3);
	EXPECT_TRUE(a == c);
	EXPECT_FALSE(a != c);
	}

	{
	const Point b(1, 3, 3.5);
	EXPECT_TRUE(a != b);
	EXPECT_FALSE(a == b);
	}

	{
	EXPECT_TRUE(a != Point());
	EXPECT_FALSE(a == Point());
	}
}

TEST(Point, Valid)
{
	{
	EXPECT_TRUE(((const Point)Point(1, 2, 3)).isvalid());
	EXPECT_FALSE(((const Point)Point(1, NAN, 3.5)).isvalid());
	EXPECT_FALSE(Point(1, 2, NAN).isvalid());
	}
	{
	Point d;
	EXPECT_FALSE(d.isvalid());
	EXPECT_EQ(-1, d.getid());
	EXPECT_TRUE(std::isnan(d.getx()));
	EXPECT_TRUE(std::isnan(d.gety()));
	}
}

TEST(Point, Distance)
{
	const Point a(1, 2, 3);

	{
	Point c(1, 2, 3);
	EXPECT_NEAR(0, Point::distance(a, c), err);
	}

	{
	const Point b(1, 1, 3.5);
	EXPECT_NEAR(sqrt(1.25), Point::distance(a, b), err);
	}

	{
	EXPECT_THROW(Point::distance(a, Point()), std::invalid_argument);
	}
}


TEST(Edge, Get)
{
	Point ap(1, 2, 3);
	Point bp(2, 3, 3.5);

	{
	EXPECT_THROW(Edge(ap, Point()), std::invalid_argument);
	}

	{
	const Edge a(ap, bp);

	EXPECT_EQ(ap, a.getfrom());
	EXPECT_EQ(bp, a.getto());
	EXPECT_NEAR(sqrt(1.25), a.getdistance(), err);
	}

	{
	Edge a(ap, bp);

	EXPECT_EQ(ap, a.getfrom());
	EXPECT_EQ(bp, a.getto());
	EXPECT_NEAR(sqrt(1.25), a.getdistance(), err);
	}

}

TEST(Edge, EQ)
{
	Point ap(1, 2, 3);
	Point bp(2, 3, 3.5);
	Point cp(3, 2, 3);
	Point dp(4, 2, 44);

	{
	const Edge a(ap, bp);
	Edge c(ap, dp);

	EXPECT_TRUE(a < c);
	EXPECT_TRUE(a == a);
	EXPECT_FALSE(a == c);
	}

	{
		Edge b(ap, cp);
		Edge c(ap, dp);
		EXPECT_FALSE(c < b);
	}
}


bool Graph_eq(const Graph & g1, const Graph & g2){
	auto e1 = g1.get_edges();
	auto e2 = g2.get_edges();
	sort(e1.begin(), e1.end());
	sort(e2.begin(), e2.end());
	return e1 == e2;
}

TEST(Graph, Creation)
{
	{
	std::vector<Point> pts({Point(1, 0, 0), Point(2, 2, 0), Point(3, 5, 3), Point(4, 1, 4)});
	std::vector<Edge> edges ({Edge(pts[0], pts[1]), Edge(pts[0], pts[2]), Edge(pts[0], pts[3]),
							 Edge(pts[1], pts[2]), Edge(pts[1], pts[3]),
							 Edge(pts[2], pts[3])}
							 );
	const Graph gph1(pts);
	Graph gph2(edges);
	EXPECT_TRUE(edges == gph1.get_edges());

	EXPECT_TRUE(Graph_eq(gph1, gph2));
	}

	{
	EXPECT_THROW(Graph({Point(), Point()}), std::invalid_argument);

	Graph empty(std::vector<Point>({}));
	EXPECT_EQ(std::vector<Edge>({}), empty.get_edges());
	}

}

TEST(Graph, KruskalEmpty)
{
	{
	Graph empty(std::vector<Point>({}));
	auto res = empty.kruskal();
	EXPECT_EQ(std::vector<Edge>({}), res.get_edges());
	}

	{
	Graph empty(std::vector<Point>({Point()}));
	auto res = empty.kruskal();
	EXPECT_EQ(std::vector<Edge>({}), res.get_edges());
	}
}

TEST(Graph, Kruskal1)
{
	std::vector<Point> pts({Point(1, 0, 0), Point(2, 2, 0), Point(3, 5, 3), Point(4, 1, 4)});
	const Graph gph1(pts);
	auto kru1 = gph1.kruskal();

	std::vector<Edge> eedges1 ({Edge(pts[0], pts[1]), Edge(pts[0], pts[3]), Edge(pts[2], pts[3])});
	Graph exp1(eedges1);

	std::vector<Edge> eedges2 ({Edge(pts[0], pts[1]), Edge(pts[1], pts[3]), Edge(pts[2], pts[3])});
	Graph exp2(eedges2);

	EXPECT_TRUE(Graph_eq(kru1, exp1) || Graph_eq(kru1, exp2));
}

TEST(Graph, Kruskal2)
{
	std::vector<Point> pts1({Point(1, 7, 5), Point(2, 3, -11),
							 Point(3, 2, -2), Point(4, -1, -8), Point(5, 14, -14)});
	Graph gph2(pts1);
	auto kru2 = gph2.kruskal();

	std::vector<Edge> eedges3 ({Edge(pts1[1], pts1[3]), Edge(pts1[2], pts1[3]),
								Edge(pts1[0], pts1[2]), Edge(pts1[1], pts1[4])});
	Graph exp3(eedges3);

	EXPECT_TRUE(Graph_eq(kru2, exp3));
}

TEST(IO, Parse)
{
	std::istringstream s1("1, 0, 0\n"
						  "2, 2, 0\n"
						  "3, 5, 3\n"
						  "4, 1, 4\n");
	auto res1 = IO::parse(s1);
	std::vector<Point> exp1({Point(1, 0, 0), Point(2, 2, 0), Point(3, 5, 3), Point(4, 1, 4)});

	EXPECT_EQ(exp1, res1);
}

TEST(IO, ParseInvalid)
{
	std::istringstream s1("1, 0, 0\n"
						  "2, 2, 0\n"
						  "aboba\n"
						  "4, 1, 4\n");
	EXPECT_THROW(IO::parse(s1), std::runtime_error);
}

TEST(IO, Print)
{
	std::vector<Point> pts1({Point(1, 0, 0), Point(2, 2, 0), Point(3, 5, 3), Point(4, 1, 4)});
	Graph g1(pts1);
	std::ostringstream s1("");
	auto edg = g1.get_edges();
	IO::print(s1, edg);

	std::string e1("1 - 2\n"
				   "1 - 3\n"
				   "1 - 4\n"
				   "2 - 3\n"
				   "2 - 4\n"
				   "3 - 4\n");

	EXPECT_EQ(e1, s1.str());
}

TEST(Unit, Test1){
	std::istringstream s1("1, 7, 5\n"
						  "2, 3, -11\n"
						  "3, 2, -2\n"
						  "4, -1, -8\n"
						  "5, 14, -14\n");

	auto inpoints = IO::parse(s1);

	std::vector<Point> expoints({Point(1, 7, 5), Point(2, 3, -11),
								 Point(3, 2, -2), Point(4, -1, -8), Point(5, 14, -14)});

	EXPECT_EQ(expoints, inpoints);

	Graph igraph(inpoints);

	Graph ograph = igraph.kruskal();

	Graph egraph({Edge(Point(2, 3, -11), Point(4, -1, -8)),
				  Edge(Point(3, 2, -2), Point(4, -1, -8)),
				  Edge(Point(1, 7, 5), Point(3, 2, -2)),
				  Edge(Point(2, 3, -11), Point(5, 14, -14))});

	EXPECT_TRUE(Graph_eq(egraph, ograph));

	std::ostringstream s2;

	IO::print(s2, ograph.get_edges());

	std::string es("2 - 4\n"
				   "3 - 4\n"
				   "1 - 3\n"
				   "2 - 5\n");
}

TEST(Unit, Test2){
	std::istringstream s1("1, 7, 6\n"
						  "7, 3, 105\n"
						  "3, 4, -2\n"
						  "4, -5, -3\n"
						  "5, 14, 14\n");

	auto inpoints = IO::parse(s1);

	std::vector<Point> expoints({Point(1, 7, 6), Point(7, 3, 105),
								 Point(3, 4, -2), Point(4, -5, -3), Point(5, 14, 14)});

	EXPECT_EQ(expoints, inpoints);

	Graph igraph(inpoints);

	Graph ograph = igraph.kruskal();

	Graph egraph({Edge(Point(1, 7, 6), Point(3, 4, -2)),
				  Edge(Point(3, 4, -2), Point(4, -5, -3)),
				  Edge(Point(1, 7, 6), Point(5, 14, 14)),
				  Edge(Point(7, 3, 105), Point(5, 14, 14))});

	EXPECT_TRUE(Graph_eq(egraph, ograph));

	std::ostringstream s2;

	IO::print(s2, ograph.get_edges());

	std::string es("1 - 3\n"
				   "3 - 4\n"
				   "1 - 5\n"
				   "7 - 5\n");
}


/*
 *
std::vector<Node> Tree::eork(){
	auto leafs = find_leafs();

	std::sort(leafs.begin(), leafs.end());
	std::queue<Node&> Q(leafs[0]);
	Node curr;

	while(!q.empty()){
		curr = Q.pop();


		Q.push(*(curr.father));
	}
}
 *
 * std::vector<Node&> Tree::find_leafs(){
	std::vector<Node&> res;

	bool check_head = 0;

	std::queue<Node&> Q({head});
	Node curr;
	while(!q.empty()){
		curr = Q.pop();

		if(curr.childs.empty()){
			curr.is_good_subtree = 1;
			curr.checked = 1;
			res.push_back(curr);
		}
		for(auto i: curr.childs){
			Q.push(i);
		}
	}
}
 *
 */
