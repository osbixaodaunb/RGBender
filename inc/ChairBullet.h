#ifndef CHAIR_BULLET_H
#define CHAIR_BULLET_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include "Log.h"
#include "Player.h"
#include <iostream>
#include <vector>

class Player;

class ChairBullet : public engine::SDLGameObject{
public:
	ChairBullet(Player* target);
	~ChairBullet();

	virtual void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);
	void load(const engine::LoaderParams* pParams);
	void draw();
	void update();
	void clean();
	void checkCollision();

	bool isActive(){
		return m_active;
	}

	void setActive(bool p_active=true){
		m_active = p_active;
	}

	void setPlayer(Player *target){
		m_player = target;
	}

private:
	double rotateTowards(engine::Vector2D);

	int m_moveSpeed;

	Player *m_player;

	Uint32 timeToLive;
	Uint32 bornTime;

	bool m_active;
};

class ChairBulletCreator{
public:
	ChairBullet* create(Player *target){
		for(auto bullet : bullets){
			if(!bullet->isActive()){
				bullet->setActive();
				bullet->setPlayer(target);
				return bullet;
			}
		}
		INFO("A new bullet was created");
		bullets.push_back(new ChairBullet(target));
		return bullets.back();
	}

private:
	std::vector<ChairBullet*> bullets;
};

#endif
