#ifndef XUXA_BOSS_H
#define XUXA_BOSS_H

#include "Enemy.h"
#include "Player.h"
#include "BossBullet.h"
#include "ChairBullet.h"	

class Player;

class XuxaBoss : public Enemy{

public:
	XuxaBoss();
	virtual void load(const engine::LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void untilt(int);
	void protect(int);
	void untiltChair(int);
	static void fullLife();
	static void halfLife();
	static void quarterLife();
	void shieldStatus(bool);
	void throwChair();

	int getShieldTime(){
		return shieldTime;
	}

	void setShieldTime(int value){
		shieldTime = value;
	}

private:
	virtual void attack();
	Player *m_player = NULL	;
	int m_fireRate;
	int shieldTime;
	BossBulletCreator bulletCreator;
	ChairBulletCreator chairBulletCreator;
};


class XuxaBossCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new XuxaBoss();
	}
};

#endif
