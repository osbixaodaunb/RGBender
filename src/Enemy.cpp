#include "Enemy.h"
#include "InputHandler.h"
#include "Game.h"
#include "MainMenuState.h"
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

void Enemy::takeDamage(int damage){
	if(damage >= 0){
		m_actualHealth -= damage;
	} else {
		m_actualHealth = 0;
	}
	INFO("HP ATUAL: ")
	INFO(m_actualHealth);

	changeState();
}

// void Enemy::takeDamage(int damage, Uint32 time){
// 	if(damage >= 0){
// 		if(m_times == 0){
// 			m_times = Timer::Instance().step() + time;
// 			m_actualHealth -= damage;
// 		}else if(Timer::Instance().step() <= m_times){
// 			m_actualHealth -= damage;
// 		}
// 		else{
// 			m_times = 0;
// 		}
// 	} else {
// 		m_actualHealth = 0;
// 	}
// 	INFO("HP ATUAL: ")
// 	INFO(m_actualHealth);

// 	changeState();
// }

void Enemy::takeDamage(int damage, Uint32 time){ //ISSO NAO VAI DA CERTO, PQ ESSA FUNCAO TERIA QUE FICAR SENDO CHAMADA SEMPRE, 
												//PRA ARRUMAR TEM Q ACHAR JEITO DE DEIXAR A LOGICA DE DAMAGE OVER TIME NO UPDATE
	if(damage >= 0){
		if(m_times == 0){
			m_times = Timer::Instance().step() + time;
			//m_actualHealth -= damage;
		}else if(Timer::Instance().step() <= m_times){
			//m_actualHealth -= damage;
		}
		else{
			m_times = 0;
		}
	} else {
		m_actualHealth = 0;
	}
	INFO("HP ATUAL: ")
	INFO(m_actualHealth);

	changeState();
}

/*bool InputHandler::isKeyDown(const std::string & key, Uint32 time){

	if(m_keystates != 0){
		if(m_keystates[m_buttons[key]] == 1 ){
			if(m_times[m_buttons[key]] == 0){
				m_times[m_buttons[key]] = Timer::Instance().step() + time;
				return true;
			} else if(Timer::Instance().step() <= m_times[m_buttons[key]]){
				return false;
			} else {
				m_times[m_buttons[key]] = 0;
			}
		}
	}

	return false;
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
		INFO("XUXA IS DEAD!");
		TextureManager::Instance().clearFromTextureMap("RAG"); //Só pra ter um feedback inicial, mas pode remover isso
		
		Game::Instance().getStateMachine()->changeState(new MainMenuState());
	}
}
