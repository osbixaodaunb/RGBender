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

private:
	enum BossHealth{
		FULL = 1,
		MEDIUM = 2,
		LOW = 3,
		DEAD = 4
	};

	int m_totalHealth;
	int m_actualHealth;
	int m_state;

	void changeAttack();
	void updateHealth();
	void changeState();
};

class EnemyCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new Enemy();
	}
};

#endif
