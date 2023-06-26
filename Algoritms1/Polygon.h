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


	struct Optional
	{
		int operator()(std::string& str)const;
	};

	double getArea(const polygon::Polygon& poly);
	double calculateArea(std::vector<Polygon>& data, int& mode);
}
#endif // !POLYGON