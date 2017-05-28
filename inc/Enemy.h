#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"

#include <string>
#include <SDL2/SDL.h>

class Enemy : public engine::SDLGameObject{
public:
	Enemy();

	void load(const engine::LoaderParams* pParams);

	void draw();
	void update();
	void clean();
	virtual void fullLife()=0;
	virtual void halfLife()=0;
	virtual void quarterLife()=0;
	typedef void(*Callback) ();

protected:

	int m_totalHealth;
	int m_actualHealth;
	
	std::vector<Callback> m_states;

	//void changeAttack();
	void updateHealth()=0;
	void changeState();
};

class EnemyCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new Enemy();
	}
};

#endif
