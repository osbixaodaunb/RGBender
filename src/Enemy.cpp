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
	SDLGameObject::update();
}

void Enemy::clean(){
	SDLGameObject::clean();
}

void Enemy::draw(){
	SDLGameObject::draw();
}

void Enemy::updateHealth(){

	if(InputHandler::Instance().isKeyDown("z")){
		m_actualHealth -= 20;
		INFO("HP ATUAL: ")
		INFO(m_actualHealth);
	}

	changeState();
}


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
		INFO("XUXA IS DEAD!");
		TextureManager::Instance().clearFromTextureMap("RAG"); //Só pra ter um feedback inicial, mas pode remover isso

	}
}