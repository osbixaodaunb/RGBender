#ifndef BULLET_H
#define BULLET_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"

#include <iostream>
#include <vector>

class Bullet : public SDLGameObject{
public:
	Bullet();
	~Bullet();

	void load(Vector2D pVelocity, Vector2D pPosition);
	void load(const LoaderParams* pParams);
	void draw();
	void update();
	void clean();

	bool isActive(){
		return m_active;
	}

	void setActive(bool p_active=true){
		m_active = p_active;
	}

private:
	double rotateTowards(Vector2D);

	int m_moveSpeed;

	Uint32 timeToLive;
	Uint32 bornTime;

	bool m_active;
};

class BulletCreator{
public:
	Bullet* create(){
		for(auto bullet : bullets){
			if(!bullet->isActive()){
				bullet->setActive();
				return bullet;
			}
		}

		std::cout << "Foi criado uma nova bullet\n";
		bullets.push_back(new Bullet());
		return bullets.back();
	}

private:
	std::vector<Bullet*> bullets;
};

#endif
