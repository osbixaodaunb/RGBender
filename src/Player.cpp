
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
	TextureManager::Instance().load("assets/bullets.png", "bullet", Game::Instance().getRenderer());

	bullet = new Bullet();
}

void Player::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);
}

void Player::draw(){
	SDLGameObject::draw();
}

void Player::update(){
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

	handleInput();

	SDLGameObject::update();
}

void Player::clean(){
	SDLGameObject::clean();
}

double dot(Vector2D a, Vector2D b){
	return a.getX()*b.getX() + a.getY()*b.getY();
}

double otoDot(Vector2D a){
	return sqrt(a.getX() * a.getX() + a.getY() * a.getY());
}

void Player::handleInput(){
	rotateTowards();
	move();
	useSkill();
	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_V, 500)){
		
		Vector2D target = InputHandler::Instance().getMousePosition() - m_position;
		target = target.norm();

		bullet->load(new LoaderParams(m_position.getX(), m_position.getY(), m_width, m_height, "bullet", 1), target);
		Game::Instance().Instance().getStateMachine()->currentState()->addGameObject(bullet);
	}
}

void Player::rotateTowards(){
	Vector2D target = InputHandler::Instance().getMousePosition() - m_position;
	target = target.norm();

	Vector2D horizontal(-1,0);

	double angle = dot(target, horizontal);
	angle /= otoDot(target);
	angle = acos(angle);

	angle = angle * 180.0 / acos(-1);

	target = InputHandler::Instance().getMousePosition() - m_position;

	if(target.getY() > 0){
		m_angle = 360 - angle;
	} else {
		m_angle = angle;
	}
}

void Player::move(){
	Vector2D move(0, 0);

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_W)){
		move += Vector2D(0, -1);
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_S)){
		move += Vector2D(0, +1);
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_D)){
		move += Vector2D(1, 0);
	}


	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_A)){
		move += Vector2D(-1, 0);
	}

	move = move.norm();

	if(!m_isDashing){
		m_velocity = move;
	}


	dash();
	m_position += m_velocity;
}

void Player::useSkill(){
	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_1, 200)){
		m_skillManager.setSkillPair(&m_pSkills, RED, &isFirstSkill);
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_2, 200)){
		m_skillManager.setSkillPair(&m_pSkills, GREEN, &isFirstSkill);
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_3, 200)){
		m_skillManager.setSkillPair(&m_pSkills, BLUE, &isFirstSkill);
	}


	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_X, 200)){
		if(m_pSkills.first != BLANK and m_pSkills.second != BLANK){
			pixelColors = m_skillManager.getSkill(m_pSkills)();
			TheTextureManager::Instance().changeColorPixels(pixelColors);
		}
		m_pSkills.first = BLANK;
		m_pSkills.second = BLANK;
		isFirstSkill = true;
		std::cout << "APERTE O X, N EH PARA APARECER NADA" << std::endl;
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
