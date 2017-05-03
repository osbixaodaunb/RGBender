#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"

#include <string>
#include <SDL2/SDL.h>

class Enemy : public SDLGameObject{
public:
	Enemy();

	void load(const LoaderParams* pParams);

	void draw();
	void update();
	void clean();
};

class EnemyCreator : public BaseCreator{
	GameObject* createGameObject() const{
		return new Enemy();
	}
};

#endif
