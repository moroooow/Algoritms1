#include "Polygon.h"
#include <fstream>


using polygon::Polygon;

int maxAreaVertexes(std::vector<Polygon>& data, std::string& str);
int minAreaVertexes(std::vector<Polygon>& data, std::string& str);

int main()
{
	

	std::string filenameShape;
	std::string filenameCommand;

	std::cout << "Enter the filename with shapes: ";
	std::cin >> filenameShape;
	std::ifstream inShape;
	inShape.open(filenameShape);

	if (!inShape.is_open())
	{
		std::cerr << "FILE IS NOT OPEN!" << std::endl;
		return -1;
	}



	std::vector<Polygon> poly;

	while (!inShape.eof())
	{

		std::copy(std::istream_iterator<Polygon>(inShape),
			std::istream_iterator<Polygon>(),
			std::back_inserter(poly));

		if (inShape.fail())
		{
			inShape.clear();
			inShape.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	std::copy(std::cbegin(poly),
		std::cend(poly),
		std::ostream_iterator<Polygon>(std::cout, "\n"));

	system("pause");
	system("cls");

	std::cout << "Enter the filename with commands: ";
	std::cin >> filenameShape;
	std::ifstream inCmd;
	inCmd.open(filenameShape);

	if (!inCmd.is_open())
	{
		std::cerr << "FILE IS NOT OPEN!" << std::endl;
		return -1;
	}

	while (!inCmd.eof())
	{
		try
		{
			std::string line;
			inCmd >> line;
			if (line == "AREA")
			{
				inCmd >> line;
				int result = polygon::accArea(poly, line);
				std::cout << "AREA " << line << std::endl << result << std::endl;
			}
			else if (line == "MAX")
			{
				inCmd >> line;
				int result = maxAreaVertexes(poly, line);
				std::cout << "MAX " << line << std::endl << result << std::endl;
			}
			else if (line == "MIN")
			{
				inCmd >> line;
				int result = minAreaVertexes(poly, line);
				std::cout << "MIN " << line << std::endl << result << std::endl;
			}
			else if (line == "COUNT")
			{
				inCmd >> line;
				int result = polygon::count(poly, line);
				std::cout << "COUNT " << line << std::endl << result << std::endl;
			}
			else if (line == "PERMS")
			{
				Polygon tmp;
				inCmd >> tmp;
				if (!inCmd)
				{
					goto clearStream;
				}
				auto fn = std::bind(polygon::countPerms,tmp, poly);
				std::cout << line <<" " << tmp.points.size() << " " << tmp << std::endl<<fn()<< std::endl;
			}
			else if (line == "MAXSEQ")
			{
				Polygon tmp;
				inCmd >> tmp;
				if (!inCmd)
				{
					goto clearStream;
				}
				auto fn = std::bind(polygon::maxSeq, tmp, poly);
				std::cout << line << " "<<tmp.points.size() << " " << tmp << std::endl << fn() << std::endl;
			}
			else
			{
			clearStream:
				inCmd.clear();
				inCmd.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw polygon::PolygonException("INVALID COMMAND");
			}
		}
		catch (polygon::PolygonException& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

int maxAreaVertexes(std::vector<Polygon>& data, std::string& str)
{
	int result;
	if (str == "AREA")
	{
		result = polygon::maxArea(data);
	}
	else if (str == "VERTEXES")
	{
		result = polygon::maxVertexes(data);
	}
	else
	{
		throw polygon::PolygonException("INVALID COMMAND");
	}
	return result;
}

int minAreaVertexes(std::vector<Polygon>& data, std::string& str)
{
	int result;
	if (str == "AREA")
	{
		result = polygon::minArea(data);
	}
	else if (str == "VERTEXES")
	{
		result = polygon::minVertexes(data);
	}
	else
	{
		throw polygon::PolygonException("INVALID COMMAND");
	}
	return result;
}