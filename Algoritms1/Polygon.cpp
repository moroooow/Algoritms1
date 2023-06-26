#include "Polygon.h"

std::ostream& polygon::operator<<(std::ostream& out, const Polygon& data)
{
	std::copy(std::cbegin(data.points),
		std::cend(data.points),
		std::ostream_iterator<Point>(out, " "));
	return out;
}

std::ostream& polygon::operator<<(std::ostream& out, const Point& data)
{
	out << '(' << data.x << ';' << data.y << ')' << " ";
	return out;
}
std::istream& polygon::operator>>(std::istream& in, Polygon& data)
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
		data = tmp;
	}
	else
	{
		in.setstate(std::ios::failbit);
	}
	return in;
}

std::istream& polygon::operator>>(std::istream& in, Point& data)
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

std::istream& polygon::operator>>(std::istream& in, DelimiterIO&& dest) {
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

double polygon::calculateArea(std::vector<Polygon>& data, int& opt)
{
	if (opt == -1)
	{
		double sum = std::accumulate(data.begin(), data.end(), 0.0,
			[&](double acc, const Polygon& pol)
			{
				if (pol.points.size() % 2 == 1)
				{
					return acc + getArea(pol);
				}
				else
				{
					return acc;
				}
			});
	}
	else if (opt == -2)
	{
		double sum = std::accumulate(data.begin(), data.end(), 0.0,
			[&](double acc, const Polygon pol)
			{
				if (pol.points.size() % 2 == 0)
				{
					return acc + getArea(pol);
				}
				else
				{
					return acc;
				}
			});
	}
	else if (opt == -3)
	{
		double sum = std::accumulate(data.begin(), data.end(), 0.0,
			[&](double acc, const Polygon pol)
			{
				return acc + getArea(pol);
			});
		return sum / data.size();
	}
	else if (opt > 0)
	{
		double sum = std::accumulate(data.begin(), data.end(), 0.0,
			[&](double acc, const Polygon pol)
			{
				if (pol.points.size() == opt)
				{
					return acc + getArea(pol);
				}
				else
				{
					return acc;
				}
			});
	}
	else
	{
		throw "<INVALID COMMAND>";
		return 0;
	}
}

double polygon::getArea(const polygon::Polygon& poly)
{
	double a = std::accumulate(poly.points.begin(), poly.points.cend(), 0.0,
		[&](double innerAcc, const polygon::Point& p) {
			size_t i = &p - &poly.points[0];
			const polygon::Point& nextPoint = poly.points[(i + 1) % poly.points.size()];
			return innerAcc + (p.x * nextPoint.y) - (p.y * nextPoint.x);
		});
	return abs(a) * 0.5;
}

int polygon::Optional::operator()(std::string& str) const
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
			 int tmp=std::stoi(str);
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
