#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "SDLGameObject.h"
#include "GameObject.h"
#include "Level.h"
#include "Log.h"

class PlayState : public engine::GameState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const {
		return s_playID;
	}

	engine::Level* getLevel(){
		return pLevel;
	}

private:
	static const std::string s_playID;
	Player* m_player;
	int m_playerLife = 100;
	engine::Level *pLevel = NULL;
	bool checkCollision(engine::SDLGameObject *p1, engine::SDLGameObject *p2);
};

#endif
