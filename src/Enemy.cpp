#include "Enemy.h"
#include "InputHandler.h"

#include <iostream>
#include <string>

using namespace std;

Enemy::Enemy() : SDLGameObject(){
	m_totalHealth = 1000;
	m_actualHealth = m_totalHealth;
	m_state = FULL;
	
}

void Enemy::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);

	}

void Enemy::update(){
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

	updateHealth();
	changeAttack();

	SDLGameObject::update();
}

void Enemy::clean(){
	SDLGameObject::clean();
}

void Enemy::draw(){
	SDLGameObject::draw();
}

void Enemy::updateHealth(){

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_Z)){
		m_actualHealth -= 20;
	}

	changeState();
}

void Enemy::changeAttack(){

	switch(m_state){
		case FULL:
			//cout << "TO FULL VIDA MANE" << endl;
		break;

		case MEDIUM:
			//cout << "TA ME DEIXANDO PISTOLA" << endl;
		break;

		case LOW:
			//cout << "Ta fudido!" << endl;
		break;

		case DEAD:
			//cout << "RIP BOSS" << endl;
		break;
	}

}

void Enemy::changeState(){
	int halfHealth = m_totalHealth / 2;
	int quarterHealth = m_totalHealth / 4;

	if(m_actualHealth <= halfHealth and m_actualHealth > quarterHealth){
		m_state = MEDIUM;
	}
	else if(m_actualHealth <= quarterHealth and m_actualHealth > 0){
		m_state = LOW;
	}
	else if(m_actualHealth <= 0){
		m_state = DEAD;
	}
}