#include "Bullet.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "Timer.h"
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"

#include <iostream>

Bullet::~Bullet(){
	std::cout << "Destruiu\n";
}

Bullet::Bullet() : SDLGameObject(){
	timeToLive = 3000;
	m_active = true;
}

void Bullet::load(const LoaderParams* pParams){
	m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}

double bulletDot(Vector2D a, Vector2D b){
	return a.getX()*b.getX() + a.getY()*b.getY();
}

double bulletOtoDot(Vector2D a){
	return sqrt(a.getX() * a.getX() + a.getY() * a.getY());
}

double Bullet::rotateTowards(Vector2D pPosition){
	Vector2D target = InputHandler::Instance().getMousePosition() - pPosition;
	target = target.norm();

	Vector2D horizontal(0,1);

	double angle = bulletDot(target, horizontal);
	angle /= bulletOtoDot(target);
	angle = acos(angle);

	angle = angle * 180.0 / acos(-1);

	target = InputHandler::Instance().getMousePosition() - pPosition;

	if(target.getX() > 0){
		std::cout << "Primeiro\n";
		return 360 - angle;
	} else {
		return angle;
	}
}
void Bullet::load(Vector2D pVelocity, Vector2D pPosition){
	double angle = rotateTowards(pPosition);

	angle += 180;

	LoaderParams* pParams = new LoaderParams(pPosition.getX(), pPosition.getY(), 100, 357, "bullet", 0, 0, 0, angle);
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	bornTime = Timer::Instance().step();
	m_velocity = pVelocity.norm() * m_moveSpeed;
}

void Bullet::draw(){
	SDLGameObject::draw();
}

void Bullet::update(){
	m_position += m_velocity;

	if(Timer::Instance().step() >= bornTime + timeToLive){
		std::cout << "Ficou inativo\n";
		m_active = false;
		Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
	}
}

void Bullet::clean(){
	SDLGameObject::clean();
}

