#ifndef XUXA_BOSS_H
#define XUXA_BOSS_H

#include "Enemy.h"

class XuxaBoss : public Enemy{

public:
	XuxaBoss();
	virtual void load(const engine::LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	static void fullLife();
	static void halfLife();
	static void quarterLife();

};


class XuxaBossCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new XuxaBoss();
	}
};

#endif