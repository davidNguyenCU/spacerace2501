#include "ObstacleMap.h"

ObstacleMap::ObstacleMap(std::string mapString)
{
	parseTextData(mapString);
}

void ObstacleMap::parseTextData(std::string mapString)
{
	//std::cout << mapString << std::endl;
	const size_t n = std::count(mapString.begin(), mapString.end(), '\n');
	std::cout << n << std::endl;

	//std::cout << mapString << std::endl;
	coordinatePairs = new glm::vec3[n];

	int charPos = 0;
	for (int i = 0; i < n; i++)
	{
		//glm::vec2 coordinatePair;

		std::string xString = "";
		float x;
		while (true)
		{
			if (mapString[charPos] == ',')
			{
				//std::cout << "Terminated @ " << mapString[charPos] << " @ " << charPos << std::endl;
				charPos++; 
				break;
			}
			xString += mapString[charPos];
			//std::cout << xString << std::endl;
			charPos++;
		}
		if (xString == "") continue;
		x = std::stod(xString);
		

		std::string yString = "";
		float y;
		while (true)
		{
			if (mapString[charPos] == '\n')
			{
				//std::cout << "Terminated @ " << mapString[charPos] << " @ " << charPos << std::endl;
				charPos++; 
				break;
			}
			yString += mapString[charPos];
			//std::cout << yString << std::endl;
			charPos++;
		}
		if (yString == "") continue;
		y = std::stod(yString);
		
		
		coordinatePairs[i] = glm::vec3(x, y, 0.0f);
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << coordinatePairs[i].x << "," << coordinatePairs[i].y << std::endl;
	}
	
	
}

glm::vec3 ObstacleMap::getObstaclePos(int index)
{
	return coordinatePairs[index];
}