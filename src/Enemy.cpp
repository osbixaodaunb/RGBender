#include "Enemy.h"

#include <string>

using namespace std;

Enemy::Enemy() : SDLGameObject(){
	m_velocity.setY(2);
	m_velocity.setX(0.001);
}

void Enemy::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);

	m_velocity.setY(2);
}

void Enemy::update(){
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

	if(m_position.getY() < 0){
		m_velocity.setY(2);
	} else if(m_position.getY() > 400){
		m_velocity.setY(-2);
	}

	SDLGameObject::update();
}

void Enemy::clean(){
	SDLGameObject::clean();
}

void Enemy::draw(){
	SDLGameObject::draw();
}
