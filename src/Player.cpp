#include "Player.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "Game.h"

#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

Player::Player() : SDLGameObject(){
	fire_rate = 500;
	TextureManager::Instance().load("assets/clash2.png", "bullet", Game::Instance().getRenderer());
}

void Player::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);
}

void Player::draw(){
	SDLGameObject::draw();
}

void Player::update(){
	m_currentFrame = int(((SDL_GetTicks() / 300) % 6));


	handleInput();

	if(m_velocity == Vector2D(0, 0)){
		m_currentFrame = 0;
	}

	SDLGameObject::update();
}

void Player::clean(){
	SDLGameObject::clean();
}

void Player::handleInput(){
	rotateTowards();
	move();

	useSkill();
	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_V, fire_rate)){
		std::cout << "FIRE RATE: " << fire_rate << std::endl;
		Vector2D pivot = Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY());

		Vector2D target = InputHandler::Instance().getMousePosition() - pivot;
		target = target.norm();
		Bullet *bullet =  bulletCreator.create();
		bullet->load(target, Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY()));
		Game::Instance().getStateMachine()->currentState()->addGameObject(bullet);
	}
}
void Player::rotateTowards(){
	Vector2D pivot = Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY());

	Vector2D target = InputHandler::Instance().getMousePosition() - pivot;
	target = target.norm();

	m_angle = Vector2D::angle(target, Vector2D(0, 1));
}

void Player::move(){
	Vector2D movement(0, 0);

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_W)){
		movement += Vector2D(0, -1);
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_S)){
		movement += Vector2D(0, +1);
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_D)){
		movement += Vector2D(1, 0);
	}


	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_A)){
		movement += Vector2D(-1, 0);
	}

	movement = movement.norm();

	if(!m_isDashing){
		m_velocity = movement;
		
	}
		
	dash();
	m_position += m_velocity;
}

void Player::useSkill(){
	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_1, 200)){
		fire_rate = 100;
		m_skillManager.setSkillPair(&m_pSkills, RED, &isFirstSkill);
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_2, 200)){
		m_skillManager.setSkillPair(&m_pSkills, GREEN, &isFirstSkill);
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_3, 200)){
		m_skillManager.setSkillPair(&m_pSkills, BLUE, &isFirstSkill);
	}


	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_X, 100)){
		std::map<std::pair<default_inks, default_inks>, bool>::iterator it = m_skillManager.getCoolDownMap()->find(m_pSkills);
		if(it != m_skillManager.getCoolDownMap()->end()){
			if(it->second == false){
				m_skillManager.setCoolDownTrigger(m_pSkills);
				if(m_pSkills.first != BLANK and m_pSkills.second != BLANK){
					pixelColors = m_skillManager.getSkill(m_pSkills)();
					TheTextureManager::Instance().changeColorPixels(pixelColors);
				}
			}
			else
				std::cout << "TA EM CD\n";
			
			m_pSkills.first = BLANK;
			m_pSkills.second = BLANK;
			isFirstSkill = true;
		}
	}
}

void Player::dash(){

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_SPACE, 1000)){
		m_dashTime = Timer::Instance().step();
		m_velocity = (m_velocity.norm() * 5);
		m_isDashing = true;
	}

	if(m_isDashing && Timer::Instance().step() >= m_dashTime + 100){
		m_isDashing = false;
	}
	
}
