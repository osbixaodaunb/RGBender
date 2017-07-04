#include "Childmaiden.h"
#include <math.h>
#include "Vector2D.h"
#include "Game.h"
#include <iostream>
using namespace std;

Childmaiden::Childmaiden(){
	isVisible = true;
	phi = 180;
	sinalx = 1;
	sinaly = 1;
	engine::Game::Instance().getStateMachine()->currentState()->addShieldObject(this);
	m_velocity = engine::Vector2D(0, 0);
}

void Childmaiden::update(){
	m_currentFrame = int(((SDL_GetTicks() / 300) % m_numFrames));
	engine::Vector2D ctr(814, 163);
	int radius = 180;
	phi = (phi + 1) % 360;
	engine::Vector2D aux;

	//	aux.setX((radius*cos(engine::Vector2D::angle(m_position, ctr)) + 814) * sinalx);
	//aux.setY(((radius*cos(engine::Vector2D::angle(m_position, ctr)) + 163) * sinaly));
	//aux = aux.norm();
	aux += engine::Vector2D(5 * sinalx, 5 * sinaly);

	if(m_position.getY() >= 280 and m_position.getX() > 780 and m_velocity.getY() > 0){
		sinaly = -1;
		sinalx = 1;
	}
	else if(m_position.getY() >= 85 and m_position.getX() >= 980 and m_velocity.getX() > 0){
		sinalx = -1;
		sinaly = -1;
	}
	else if(m_position.getX() < 780 and m_position.getY() < 30 and m_velocity.getY() < 0){
		sinaly = 1;
		sinalx = -1;
	}
	else if(m_position.getX() < 600 and m_position.getY() >= 85 and m_velocity.getX() < 0){
		sinalx = 1;
		sinaly = 1;
	}

	m_velocity = aux;
	m_position += m_velocity;
}

void Childmaiden::load(const engine::LoaderParams *pParams){
	SDLGameObject::load(pParams);
}

void Childmaiden::draw(){
	if(isVisible)
		SDLGameObject::draw();
}

void Childmaiden::clean(){
	SDLGameObject::clean();
}