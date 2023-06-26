#pragma once
#ifndef POLYGON
#define POLYGON
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include "cmath"

namespace polygon
{

	struct Point
	{
		int x, y;
	};

	struct DelimiterIO
	{
		char exp;
	};

	struct IntIO
	{
		int& ref;
	};

	struct Polygon
	{
		std::vector<Point> points;
	};
	
	std::ostream& operator<<(std::ostream& out, const Polygon& data);
	std::ostream& operator<<(std::ostream& out, const Point& data);
	std::istream& operator>>(std::istream& in, Polygon& data);
	std::istream& operator>>(std::istream& in, Point& data);
	std::istream& operator>>(std::istream& in, DelimiterIO&& dest);


	struct OptionalArea
	{
		int operator()(std::string& str)const;
	};

	struct OptionalCount
	{
		int operator()(std::string& str)const;
	};

	double maxArea(std::vector<Polygon>& data);
	int maxVertexes(std::vector<Polygon>& data);
	int minVertexes(std::vector<Polygon>& data);
	double minArea(std::vector<Polygon>& data);
	double calculateArea(const polygon::Polygon& poly);
	double accArea(std::vector<Polygon>& data, std::string str);
	int count(std::vector<Polygon>& data, std::string str);

}
#endif // !POLYGON