#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "BaseCreator.h"

#include <string>
#include <map>

class GameObjectFactory{
public:
	static GameObjectFactory& Instance(){
		static GameObjectFactory instance;

		return instance;
	}

	GameObjectFactory(GameObjectFactory const&) = delete;
	void operator=(GameObjectFactory const&) = delete;

	bool registerType(std::string typeID, BaseCreator* pCreator);

	GameObject* create(std::string typeID);

private:
	GameObjectFactory(){};
	std::map<std::string, BaseCreator*> m_creators;
};

#endif
