#include "Enemy.h"
#include "InputHandler.h"
#include "Log.h"
#include <iostream>
#include <string>

using namespace std;
using namespace engine;

Enemy::Enemy() : SDLGameObject(){
	m_totalHealth = 1000;
	m_actualHealth = m_totalHealth;
}

void Enemy::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);
}

void Enemy::update(){
	m_currentFrame = int(((SDL_GetTicks() / 200) % m_numFrames));

	SDLGameObject::update();
}

void Enemy::clean(){
	SDLGameObject::clean();
}

void Enemy::draw(){
	SDLGameObject::draw();
}