#include "Player.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "InputHandler.h"

#include <string>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

Player::Player() : SDLGameObject(){

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

void Player::handleInput(){
	if(InputHandler::Instance().joysticksInitialised()){
		int t_x = InputHandler::Instance().xvalue(0,1);
		int t_y = InputHandler::Instance().yvalue(0,1);

		Vector2D velocity(t_x, t_y);
		velocity = velocity.norm();

		int boost = 1;
	
		if(InputHandler::Instance().getButtonState(0, 0)){
				boost = 3;
		}

		m_velocity.setX(boost * velocity.getX());
		m_velocity.setY(boost * velocity.getY());		
	}

	Vector2D target = InputHandler::Instance().getMousePosition();
	m_velocity = target - m_position;
	m_velocity /= 50;
}
