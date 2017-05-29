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
	updateHealth();
	//changeAttack();

	SDLGameObject::update();
}

void Enemy::clean(){
	SDLGameObject::clean();
}

void Enemy::draw(){
	SDLGameObject::draw();
}

void Enemy::updateHealth(){

	if(InputHandler::Instance().isKeyDown("y")){
		m_actualHealth -= 20;
		printf("ENTROU AQUI REALLY\n");
		printf("ACTUAL: %d\n", m_actualHealth);
		printf("TOTAL: %d\n", m_totalHealth);
	}

	changeState();
}

/*void Enemy::changeAttack(){

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

}*/

void Enemy::changeState(){
	int halfHealth = m_totalHealth / 2;
	int quarterHealth = m_totalHealth / 4;
	if(m_actualHealth <= halfHealth and m_actualHealth > quarterHealth){
		if(m_states.size() == 3){
			m_states.pop_back();
			m_states.back()(); //Executa a funcao half life
		}
		
	}
	else if(m_actualHealth <= quarterHealth and m_actualHealth > 0){
		if(m_states.size() == 2){
			m_states.pop_back();
			m_states.back()(); //Executa a funcao quarter life	
		}
		
	}
	else if(m_actualHealth <= 0){
		INFO("XUXA IS DEAD!")
	}
}
