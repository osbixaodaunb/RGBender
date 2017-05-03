#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameObject.h"

#include <string>
#include <vector>

class GameState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter() = 0;
	virtual bool onExit();

	virtual std::string getStateID() const = 0;

	virtual ~GameState() {}

	// COISA MAIS MIGUE QUE UE JA FIZ NA MINHA VIDA
	bool can_update = true;
protected:
	std::vector<GameObject*> m_gameObjects;
	std::vector<std::string> m_textureIDList;
	
};

#endif
