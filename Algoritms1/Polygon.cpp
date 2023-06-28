#include "Polygon.h"



namespace polygon
{
	std::ostream& operator<<(std::ostream& out, const Polygon& data)
	{
		std::copy(std::cbegin(data.points),
			std::cend(data.points),
			std::ostream_iterator<Point>(out, " "));
		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Point& data)
	{
		out << '(' << data.x << ';' << data.y << ')' << " ";
		return out;
	}
	std::istream& operator>>(std::istream& in, Polygon& data)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		Polygon tmp;
		size_t count;
		{
			in >> count;
			if (count < 3)
			{
				in.setstate(std::ios::failbit);
				return in;
			}
			for (int i = 0; i < count; i++)
			{
				if (in.peek() == '\n')
				{
					break;
				}
				Point a;
				in >> a;
				tmp.points.push_back(a);
			}
		}
		if (in && (in.peek() == '\n' || in.eof()) && tmp.points.size() == count)
		{
			std::sort(tmp.points.begin(), tmp.points.end(),
				[](Point& a, Point& b)
				{
					if (a.x != b.x)
					{
						return a.x < b.x;
					}
					else
					{
						return a.y < b.y;
					}
				});
			data = tmp;
		}
		else
		{
			in.setstate(std::ios::failbit);
		}
		return in;
	}

	std::istream& operator>>(std::istream& in, Point& data)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		Point tmp;
		in >> DelimiterIO{ '(' } >> tmp.x >> DelimiterIO{ ';' };
		in >> tmp.y >> DelimiterIO{ ')' };

		if (in)
		{
			data = tmp;
		}
		return in;
	}

	std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		char c = '0';
		in >> c;
		if (in && (c != dest.exp))
		{
			in.setstate(std::ios::failbit);
		}
		return in;
	}

	double accArea(std::vector<Polygon>& data, std::string str)
	{
		polygon::OptionalArea t;
		int opt = t(str);
		double sum;
		if (opt == -1)
		{
			sum = std::accumulate(data.begin(), data.end(), 0.0,
				[&](double acc, const Polygon& pol)
				{
					if (pol.points.size() % 2 == 1)
					{
						return acc + calculateArea(pol);
					}
					else
					{
						return acc;
					}
				});
		}
		else if (opt == -2)
		{
			sum = std::accumulate(data.begin(), data.end(), 0.0,
				[&](double acc, const Polygon pol)
				{
					if (pol.points.size() % 2 == 0)
					{
						return acc + calculateArea(pol);
					}
					else
					{
						return acc;
					}
				});
		}
		else if (opt == -3)
		{
			sum = std::accumulate(data.begin(), data.end(), 0.0,
				[&](double acc, const Polygon pol)
				{
					return acc + calculateArea(pol);
				});
			return sum / data.size();
		}
		else if (opt > 0)
		{
			sum = std::accumulate(data.begin(), data.end(), 0.0,
				[&](double acc, const Polygon pol)
				{
					if (pol.points.size() == opt)
					{
						return acc + calculateArea(pol);
					}
					else
					{
						return acc;
					}
				});
		}
		else
		{
			throw PolygonException("INVALID COMMAND");
		}
		return sum;
	}

	double calculateArea(const Polygon& poly)
	{
		double a = std::accumulate(poly.points.begin(), poly.points.cend(), 0.0,
			[&](double innerAcc, const polygon::Point& p) {
				size_t i = &p - &poly.points[0];
				const polygon::Point& nextPoint = poly.points[(i + 1) % poly.points.size()];
				return innerAcc + (p.x * nextPoint.y) - (p.y * nextPoint.x);
			});
		return abs(a) * 0.5;
	}

	int OptionalArea::operator()(std::string& str) const
	{
		if (str == "ODD")
		{
			return -1;
		}
		else if (str == "EVEN")
		{
			return -2;
		}
		else if (str == "MEAN")
		{
			return -3;
		}
		else
		{
			try
			{
				int tmp = std::stoi(str);
				int digit = static_cast<int>(std::log10(abs(tmp))) + 1;
				if (digit == str.size())
				{
					return tmp;
				}
				else
				{
					return 0;
				}
			}
			catch (const std::exception&)
			{
				return 0;
			}
		}
	}

	int OptionalCount::operator()(std::string& str) const
	{
		if (str == "ODD")
		{
			return -1;
		}
		else if (str == "EVEN")
		{
			return -2;
		}
		else
		{
			try
			{
				int tmp = std::stoi(str);
				int digit = static_cast<int>(std::log10(abs(tmp))) + 1;
				if (digit == str.size())
				{
					return tmp;
				}
				else
				{
					return 0;
				}
			}
			catch (const std::exception&)
			{
				return 0;
			}
		}
	}

	int maxVertexes(std::vector<Polygon>& data)
	{
		Polygon tmp = *std::max_element(data.begin(), data.end(),
			[](const Polygon& a, const Polygon& b)
			{
				return a.points.size() < b.points.size();
			});
		return tmp.points.size();
	}

	int minVertexes(std::vector<Polygon>& data)
	{
		Polygon tmp = *std::min_element(data.begin(), data.end(),
			[](const Polygon& a, const Polygon& b)
			{
				return a.points.size() < b.points.size();
			});
		return tmp.points.size();
	}

	double maxArea(std::vector<Polygon>& data)
	{
		Polygon tmp = *std::max_element(data.begin(), data.end(),
			[](const Polygon& a, const Polygon& b)
			{
				return calculateArea(a) < calculateArea(b);
			});
		return calculateArea(tmp);
	};

	double minArea(std::vector<Polygon>& data)
	{
		Polygon tmp = *std::min_element(data.begin(), data.end(),
			[](const Polygon& a, const Polygon& b)
			{
				return calculateArea(a) < calculateArea(b);
			});
		return calculateArea(tmp);
	}

	int count(std::vector<Polygon>& data, std::string str)
	{
		OptionalCount t;
		int opt = t(str);

		if (opt == -1)
		{
			return std::count_if(data.begin(), data.end(),
				[](const Polygon& a)
				{
					return a.points.size() % 2 == 1;
				});
		}
		else if (opt == -2)
		{
			return std::count_if(data.begin(), data.end(),
				[](const Polygon& a)
				{
					return a.points.size() % 2 == 0;
				});
		}
		else if (opt == 0)
		{
			throw PolygonException("INVALID COMMAND");
			return 0;
		}
		else
		{
			return std::count_if(data.begin(), data.end(),
				[&](const Polygon& a)
				{
					return a.points.size() == opt;
				});
		}
	}

	int countPerms(Polygon& data,std::vector<Polygon>& src)
	{
		return std::count_if(src.begin(), src.end(),
			[&](Polygon& a)
			{
				return a == data;
			});
	}

	bool operator==(Point a,  Point b)
	{
		return (a.x == b.x) && (a.y == b.y);
	}

	bool operator==(Polygon a,Polygon b)
	{
		return a.points == b.points;
	}

	int maxSeq(Polygon& data, std::vector<Polygon>& src)
	{
		int max;
		int sum = std::accumulate(src.begin(), src.end(),0,
			[&](int acc, Polygon pol)
			{
				if (data == pol)
				{
					return acc + 1;
				}
				else
				{
					max = std::max(acc, max);
					acc = 0;
					return acc;
				}
			});
		max = std::max(sum, max);
		return max;
	}
}