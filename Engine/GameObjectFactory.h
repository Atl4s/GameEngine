
#pragma once

#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator
{
public:
	
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
protected:

	static GameObjectFactory* s_pInstance;
	GameObjectFactory(){}
	virtual ~GameObjectFactory(){}

public:

	static GameObjectFactory* Instance()
	{
		if (s_pInstance == 0)  { s_pInstance = new GameObjectFactory();    return s_pInstance; }
		return s_pInstance;
	}

	static bool DeleteInstance()
	{
		if (s_pInstance)
		{
			delete s_pInstance;
			s_pInstance = 0;
			return true;
		}
		return false;
	}

	bool registerType(std::string typeID, BaseCreator* pCreator) //looking for concrete creator(if it already exist return false)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it != m_creators.end())
		{
			delete pCreator;
			return false;
		}

		m_creators[typeID] = pCreator;

		return true;
	}

	GameObject* create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			return nullptr;
		}

		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();
	}

private:

	std::map<std::string, BaseCreator*> m_creators;

};