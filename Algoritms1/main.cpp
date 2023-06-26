#include "Polygon.h"
#include <fstream>
#include <numeric>

int main()
{
	using polygon::Polygon;
	using namespace std::placeholders;

	std::ifstream in;
	in.open("shapes.txt");
	std::vector<Polygon> poly;

	while (!in.eof())
	{
		
		std::copy(std::istream_iterator<Polygon>(in),
			std::istream_iterator<Polygon>(),
			std::back_inserter(poly));

		if (in.fail())
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}


	std::copy(std::cbegin(poly),
		std::cend(poly),
		std::ostream_iterator<Polygon>(std::cout, "\n"));
		
	try
	{
		std::cout<<polygon::count(poly,"3");
	}
	catch (...)
	{
		std::cout << "<INVALID COMMAND>";
	}
}