#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"

#include <string>
#include <SDL2/SDL.h>
#include <vector>

class Enemy : public engine::SDLGameObject{
public:
	Enemy();

	void load(const engine::LoaderParams* pParams);

	void draw();
	void update();
	void clean();
	// virtual void fullLife();
	// virtual void halfLife();
	// virtual void quarterLife();
	typedef void(*Callback) ();
	void updateHealth();

protected:

	int m_totalHealth;
	int m_actualHealth;
	std::vector<Callback> m_states;

	//void changeAttack();
	void changeState();
};

// class EnemyCreator : public engine::BaseCreator{
// 	engine::GameObject* createGameObject() const{
// 		return new Enemy();
// 	}
// };

#endif
