#ifndef XUXA_BOSS_H
#define XUXA_BOSS_H

#include "Enemy.h"
#include "Player.h"
#include "BossBullet.h"

class Player;

class XuxaBoss : public Enemy{

public:
	XuxaBoss();
	virtual void load(const engine::LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void untilt(int);
	static void fullLife();
	static void halfLife();
	static void quarterLife();

private:
	virtual void attack();
	Player *m_player = NULL	;
	int m_fireRate;
	BossBulletCreator bulletCreator;
};


class XuxaBossCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new XuxaBoss();
	}
};

#endif
