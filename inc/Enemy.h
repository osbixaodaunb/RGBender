#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"
#include "Timer.h"

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
	Uint32 getEnemyTime(){
		return m_times;
	}

	void setEnemyTime(Uint32 time){
		m_times = engine::Timer::Instance().step() + time;
	}
	int getHealth(){
		return m_actualHealth;
	}
protected:

	int m_totalHealth;
	int m_actualHealth;
	Uint32 m_times;
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
