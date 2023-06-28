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
#include "exception"

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
	
	class PolygonException: public std::exception
	{
	private:
		std::string reason_;

	public:
		PolygonException(std::string reason) : reason_(reason) {};

		const char* what() const noexcept override
		{
			return reason_.c_str();
		}
	};

	bool operator==( Point a,Point b);
	bool operator==(Polygon a, Polygon b);

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

	int countPerms(Polygon& data,std::vector<Polygon>& src);

	int maxSeq(Polygon& data, std::vector<Polygon>& src);

}
#endif // !POLYGON