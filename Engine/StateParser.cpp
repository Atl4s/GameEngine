#include "StateParser.h"
#include "Vertex.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects)
{

	tinyxml2::XMLDocument xmlDoc;

	tinyxml2::XMLError eResult = xmlDoc.LoadFile(stateFile);
	std::cout << "open " << stateFile << std::endl;

	tinyxml2::XMLElement* pRoot = xmlDoc.RootElement();//root element

	tinyxml2::XMLElement* pStateRoot = 0;

	for (tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e; e = e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;//looking for a necessary state
			std::cout << "open element " << pStateRoot->Value()<< std::endl;
		}
	}

	tinyxml2::XMLElement*pTextureRoot = 0;


	tinyxml2::XMLElement* pObjectRoot = 0;
	for (tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("OBJECTS"))
		{
			pObjectRoot = e;
			std::cout << "open element " << pObjectRoot->Value()<< std::endl;
		}
	}

	parseObjects(pObjectRoot, pObjects);
	std::cout << "parse objects" << std::endl;
	return true;
}

void StateParser::parseObjects(tinyxml2::XMLElement *pStateRoot, std::vector<GameObject*> *pObjects)
{
	for (tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string texturePath;

		x = e->IntAttribute("x");
		y = e->IntAttribute("y");
		width = e->IntAttribute("width");
		height = e->IntAttribute("height");
		numFrames = e->IntAttribute("numFrames");
		callbackID = e->IntAttribute("callbackID");
		animSpeed = e->IntAttribute("animSpeed");
		texturePath = e->Attribute("texture");
		std::cout << texturePath << std::endl;

		glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
		GameObject* pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));
		pGameObject->load(new LoaderParams(x, y, width, height, texturePath, color, numFrames, callbackID, animSpeed));
		pObjects->push_back(pGameObject);
	}
	std::cout << "parseObjects complete" << std::endl;
}
