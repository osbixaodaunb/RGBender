#include "Player.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "InputHandler.h"

#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

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

double dot(Vector2D a, Vector2D b){
	return a.getX()*b.getX() + a.getY()*b.getY();
}

double otoDot(Vector2D a){
	return sqrt(a.getX() * a.getX() + a.getY() * a.getY());
}

void Player::handleInput(){
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

	//std::cout << angle << std::endl;

}
