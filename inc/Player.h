#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"
#include "Bullet.h"
#include "Timer.h"
#include <string>
#include <SDL2/SDL.h>

class Player : public SDLGameObject{
public:
	Player();

	void load(const LoaderParams* pParams);
	void draw();
	void update();
	void clean();

private:
	void handleInput();
	void move();
	void rotateTowards();
	void dash();
	bool m_canDash;
	Uint32 m_dashTime;

	bool teste = true;
	Bullet *bullet;

};

class PlayerCreator : public BaseCreator{
	GameObject* createGameObject() const{
		return new Player();
	}
};

#endif
