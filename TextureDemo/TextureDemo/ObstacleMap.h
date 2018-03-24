#pragma once

#include <string>
#include <iostream>
#include "ResourceManager.h"
#include <glm\glm.hpp>

class ObstacleMap {
public:
	ObstacleMap(std::string mapString);

	glm::vec3 getObstaclePos(int index);

private:
	void parseTextData(std::string mapString);
	glm::vec3 * coordinatePairs;

};

