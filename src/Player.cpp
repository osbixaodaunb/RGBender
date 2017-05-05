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
	m_canDash = true;
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

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_V, 1000)){
		
		Vector2D target = InputHandler::Instance().getMousePosition() - m_position;
		target = target.norm();

		bullet->load(new LoaderParams(m_position.getX(), m_position.getY(), m_width, m_height, "bullet", 1), target);
		Game::Instance().Instance().getStateMachine()->currentState()->addGameObject(bullet);
	}

	//std::cout << angle << std::endl;
}

void Player::rotateTowards(){
	std::cout << InputHandler::Instance().getMousePosition().getX() << std::endl;

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

	if(m_canDash){
		m_velocity = move;
	}

	dash();
	m_position += m_velocity;
}

void Player::dash(){

	bool dashPressed = false;
	if(m_canDash){
		dashPressed = InputHandler::Instance().isKeyDown(SDL_SCANCODE_SPACE);
		if(dashPressed and m_canDash){
			m_velocity = (m_velocity * 5);
			m_canDash = false;
			m_dashTime = Timer::Instance().step();
		}
	}
	else if(Timer::Instance().step() >= m_dashTime + 100){
			m_canDash = true;
		}
}
