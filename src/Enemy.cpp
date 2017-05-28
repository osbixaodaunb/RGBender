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
	m_state.push_back(&Enemy::quarterLife());
	m_state.push_back(&Enemy::halfLife());
	m_state.push_back(&Enemy::fullLife());
	m_state.back()(); //Deve iniciar/executar o primeiro estado "FULL LIFE"
}

void Enemy::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);
}

void Enemy::update(){
	m_currentFrame = int(((SDL_GetTicks() / 200) % m_numFrames));
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

/*void Enemy::updateHealth(){

	if(InputHandler::Instance().isKeyDown("z")){
		m_actualHealth -= 20;
	}

	changeState();
}*/

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
		m_state.pop_back();
		m_state.back()(); //Executa a funcao half life
	}
	else if(m_actualHealth <= quarterHealth and m_actualHealth > 0){
		m_state.pop_back();
		m_state.back()(); //Executa a funcao quarter life
	}
	else if(m_actualHealth <= 0){
		//TODO
	}
}
