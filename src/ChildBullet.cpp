#include "ChildBullet.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "Timer.h"
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"
#include "Enemy.h"
#include "Physics.h"
#include "GameOverState.h"
#include <iostream>

using namespace engine;

ChildBullet::~ChildBullet(){
	INFO("REMOVE CHAIR BULLET");
}

ChildBullet::ChildBullet(Player *target) : SDLGameObject(){
	setPlayer(target);
	timeToLive = 5000;
	m_active = true;
}

void ChildBullet::load(const LoaderParams* pParams){
	m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}

double ChildBullet::rotateTowards(Vector2D pPosition){
	Vector2D target = InputHandler::Instance().getMousePosition() - pPosition;
	target = target.norm();

	Vector2D horizontal(0,1);

	return Vector2D::angle(target, Vector2D(0, 1));
}
void ChildBullet::load(Vector2D pVelocity, Vector2D pPosition){
	double angle = rotateTowards(pPosition);

	m_moveSpeed = 8;
	LoaderParams* pParams = new LoaderParams(pPosition.getX(), pPosition.getY(), 40, 60, "childBullet", 0, 0, 0, angle);
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	bornTime = Timer::Instance().step();
	m_velocity = pVelocity.norm() * m_moveSpeed;
	//m_velocity = Vector2D(0.5, 0.5);
}

void ChildBullet::draw(){
	SDLGameObject::draw();
}

void ChildBullet::update(){
	m_textureID = "child";
	m_position += m_velocity;

	if(Timer::Instance().step() >= bornTime + timeToLive){
		m_active = false;
		Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
	}

	checkCollision();

}

void ChildBullet::checkCollision(){
	if(m_active){
		Vector2D pos = m_player->getPosition();
		Vector2D thisPos = getPosition();
		
		if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(m_player), dynamic_cast<SDLGameObject*>(this))){
			m_active = false;
			Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
			INFO("Bullet collided");
			INFO("PLAYER LOST THE GAME");
			m_player->setLife((m_player->getLife()) - 50);
		}
	}
}

void ChildBullet::clean(){
	SDLGameObject::clean();
}

