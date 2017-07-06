#include "Bullet.h"
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
#include <iostream>
#include <string>
#include "Childmaiden.h"
using namespace engine;

Bullet::~Bullet(){
	INFO("Bullet destroyed")
}

Bullet::Bullet(Enemy *p_boss) : SDLGameObject(){

	setBoss(p_boss);

	timeToLive = 1000;
	m_active = true;
}

void Bullet::load(const LoaderParams* pParams){
	m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}

double Bullet::rotateTowards(Vector2D pPosition){
	Vector2D target = InputHandler::Instance().getMousePosition() - pPosition;
	target = target.norm();

	Vector2D horizontal(0,1);

	return Vector2D::angle(target, Vector2D(0, 1));
}
void Bullet::load(Vector2D pVelocity, Vector2D pPosition){
	double angle = rotateTowards(pPosition);

	m_moveSpeed = 5;
	LoaderParams* pParams = new LoaderParams(pPosition.getX(), pPosition.getY(), 16, 16, "bullet", 0, 0, 0, angle);
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	bornTime = Timer::Instance().step();
	m_velocity = pVelocity.norm() * m_moveSpeed;
}

void Bullet::draw(){
	SDLGameObject::draw();
}

void Bullet::update(){
	//std::cout << "Bullet top: " << getPosition().getY() + (getHeight() - getCollider().getHeight())/2 << std::endl;
	m_position += m_velocity;

	if(Timer::Instance().step() >= bornTime + timeToLive){
		m_active = false;
		Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
	}
	checkCollision();

}

void Bullet::checkCollision(){
	if(m_active){
		Vector2D pos = m_boss->getPosition();
		Vector2D thisPos = getPosition();
		
		
		for(auto obj : engine::Game::Instance().getStateMachine()->currentState()->getShieldObjects()){
			if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(obj), dynamic_cast<SDLGameObject*>(this))){
				if(dynamic_cast<Childmaiden*>(obj)->getVisibility()){
					INFO("REMOVENDO BALA");
					m_active = false;
					Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
					INFO("Bullet collided with shield");
				}
				else{
					break;
				}
			}
		}

		if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(m_boss), dynamic_cast<SDLGameObject*>(this))){
			m_active = false;
			Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
			m_boss->takeDamage(100);
			if(m_venemous){
				INFO("VENEMOUS TRUE");
				m_collided = true;
				m_boss->setEnemyTime(300);
			}
			
			int score = Game::Instance().getScore();
			Game::Instance().setScore(score + 10);
			TextureManager::Instance().loadText(std::to_string(Game::Instance().getScore()), "assets/fonts/Lato-Regular.ttf", "score", {255,255,255}, 50, Game::Instance().getRenderer());
			INFO("Bullet collided with boss");
		}


	}
}

void Bullet::clean(){
	SDLGameObject::clean();
}

