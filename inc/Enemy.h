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

	virtual void load(const engine::LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	typedef void(*Callback) ();
	void takeDamage(int);

protected:

	int m_totalHealth;
	int m_actualHealth;
	std::vector<Callback> m_states;

	//void changeAttack();
	void changeState();

};

/*
class EnemyCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new Enemy();
	}
};
*/

#endif
