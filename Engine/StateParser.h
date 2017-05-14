#pragma once

#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "ResourceManager.h"
#include "GLTexture.h"

class GameObject;

class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects);

private:

	void parseObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*> *pObjects);
};