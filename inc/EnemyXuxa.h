#ifndef ENEMY_XUXA_H
#define ENEMY_XUXA_H
#include "Enemy.h"
#include "BaseCreator.h"

class EnemyXuxa : public Enemy{
public:
	EnemyXuxa();
	void update();
	void draw();
	void clean();

	static void fullLife();
	static void halfLife();
	static void quarterLife();
	//void updateHealth();
};

class EnemyCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new EnemyXuxa();
	}
};

#endif