#include "ChairBullet.h"
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

ChairBullet::~ChairBullet(){
	INFO("REMOVE CHAIR BULLET");
}

ChairBullet::ChairBullet(Player *target) : SDLGameObject(){
	setPlayer(target);
	timeToLive = 5000;
	m_active = true;
}

void ChairBullet::load(const LoaderParams* pParams){
	m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}

double ChairBullet::rotateTowards(Vector2D pPosition){
	Vector2D target = InputHandler::Instance().getMousePosition() - pPosition;
	target = target.norm();

	Vector2D horizontal(0,1);

	return Vector2D::angle(target, Vector2D(0, 1));
}
void ChairBullet::load(Vector2D pVelocity, Vector2D pPosition){
	double angle = rotateTowards(pPosition);

	m_moveSpeed = 7;
	LoaderParams* pParams = new LoaderParams(pPosition.getX(), pPosition.getY(), 60, 96, "chairBullet", 0, 0, 0, angle, 55, 80);
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	bornTime = Timer::Instance().step();
	m_velocity = pVelocity.norm() * m_moveSpeed;
	//m_velocity = Vector2D(0.5, 0.5);
}

void ChairBullet::draw(){
	SDLGameObject::draw();
}

void ChairBullet::update(){

	m_position += m_velocity;

	if(Timer::Instance().step() >= bornTime + timeToLive){
		m_active = false;
		Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
	}

	checkCollision();

}

void ChairBullet::checkCollision(){
	if(m_active){
		Vector2D pos = m_player->getPosition();
		Vector2D thisPos = getPosition();
		
		if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(m_player), dynamic_cast<SDLGameObject*>(this))){
			m_active = false;
			Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
			INFO("Bullet collided");
			INFO("PLAYER LOST THE GAME");
			if(!m_player->getShieldActive()){
				m_player->setLife((m_player->getLife()) - 30);
				m_player->setPlayerMoves(false);
				m_player->setStunTime(Timer::Instance().step());
			}
			else if(m_player->getShieldActive())
				m_player->setShieldHits();
			
			//Game::Instance().getStateMachine()->changeState(new GameOverState());
		}
	}
}

void ChairBullet::clean(){
	SDLGameObject::clean();
}

