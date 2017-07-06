#ifndef SHIELDSKILL_H
#define SHIELDSKILL_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include "Log.h"
#include "Enemy.h"
#include <iostream>
#include <vector>

class ShieldSkill : public engine::SDLGameObject{
public:
	ShieldSkill();
	~ShieldSkill();

	void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);
	void load(const engine::LoaderParams* pParams);
	void draw();
	void update();
	void clean();
	void checkCollision();

private:
	Enemy* m_boss = NULL;
	bool m_active;
	int numberHits;
};

#endif