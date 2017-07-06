#include "Player.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "Game.h"
#include "Log.h"
#include "Enemy.h"
#include "PlayState.h"
#include "Physics.h"
#include "AudioManager.h"
#include "GameOverState.h"
#include "Childmaiden.h"
#include "Timer.h"

#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace engine;

Player::Player() : SDLGameObject(){
	m_fireRate = 500;
	TextureManager::Instance().load("assets/bullet.png", "bullet", Game::Instance().getRenderer());
	TextureManager::Instance().load("assets/health.png", "health", Game::Instance().getRenderer());
	TextureManager::Instance().load("assets/circle.png", "instance", Game::Instance().getRenderer());
	TextureManager::Instance().load("assets/teste.png", "childBullet", Game::Instance().getRenderer());

	INFO("Player inicializado");
	m_life = 100;
	canMove = true;
}

void Player::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);
}

void Player::draw(){
	SDLGameObject::draw();
}

void Player::update(){
	//std::cout << "Player top: " << getPosition().getY() + (getHeight() - getCollider().getHeight())/2 << std::endl;

	if(m_life <= 0){
		Game::Instance().getStateMachine()->changeState(new GameOverState());
	}
	if(Game::Instance().getStateMachine()->currentState()->getStateID() == "PLAY"){
		PlayState *playState = dynamic_cast<PlayState*>(Game::Instance().getStateMachine()->currentState());
		if(playState->getLevel() != NULL && m_boss == NULL){
			INFO("Xuxa is set");
			m_boss = playState->getLevel()->getXuxa();
		}
	}


	if(!canMove){
		int time = Timer::Instance().step() - getStunTime();
		if(time >= 700){
			canMove = true;
		}

		rotateTowards();
	}

	if(canMove){
		handleInput();
	}

	SDLGameObject::update();
}

void Player::clean(){
	SDLGameObject::clean();
}

void Player::handleInput(){
	move();

	m_numFrames = 4;
	m_currentFrame = 1;

	if(m_velocity == Vector2D(0, 0)){
		rotateTowards();
	} else {
		Vector2D vec[] = {Vector2D(0,-1), Vector2D(1, -1).norm(), Vector2D(1, 0), Vector2D(1, 1).norm(), Vector2D(0, 1), Vector2D(-1, 1).norm(), Vector2D(-1, 0), Vector2D(-1, -1).norm()};
		for(int i=0; i<8; i++){
			if(m_velocity.norm() == vec[i]){
				changeSprite(i);
			}
		}
		int tmp = m_currentFrame;
		m_currentFrame = 1 + int(((SDL_GetTicks() / 100) % (m_numFrames-1)));
	}
	useSkill();
	if(InputHandler::Instance().getMouseButtonState(LEFT, m_fireRate)){
		count = Timer::Instance().step() + 300;
		AudioManager::Instance().playChunk("assets/sounds/shot.wav");
		INFO("FIRE RATE: " + m_fireRate);
		Vector2D pivot = Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY());
		Vector2D target = InputHandler::Instance().getMousePosition() - pivot;
		target = target.norm();
		Bullet *bullet =  bulletCreator.create(m_boss);
		bullet->load(target, Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY()));
		Game::Instance().getStateMachine()->currentState()->addGameObject(bullet);
	}
}

bool inside(double angle, double value){
	return value > angle - 22.5 && value < angle + 22.5;
}

void Player::changeSprite(int index){
	m_flip = false;
	switch(index){
		case 0: // UP
			m_textureID = "up";
			break;
		case 1: // UP-RIGHT
			m_textureID = "upright";
			break;
		case 2: // RIGHT
			m_flip = true;
			m_textureID = "left";
			break;
		case 3: // DOWN-RIGHT
			m_flip = true;
			m_textureID = "downleft";
			break;
		case 4: // DOWN
			m_textureID = "down";
			break;
		case 5: // DOWN-LEFT
			m_textureID = "downleft";
			break;
		case 6: // LEFT
			m_textureID = "left";
			break;
		case 7: // UP-LEFT
			m_flip = true;
			m_textureID = "upright";
			break;
	}
	if(!canMove){
		m_textureID += "stun";
	} else if(Timer::Instance().step() < count){
		m_textureID += "attack";
	}
}

void Player::rotateTowards(){
	m_numFrames = 1;
	m_currentFrame = 0;
	Vector2D pivot = Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY());

	Vector2D target = InputHandler::Instance().getMousePosition() - pivot;
	target = target.norm();


	double angle = Vector2D::angle(target, Vector2D(0, 1));
	
	for(int i=0; i<8; i++){
		if(inside(45 * i, angle)){
			changeSprite(i);
			break;
		}
	}

}

void Player::move(){
	Vector2D movement(0, 0);

	if(InputHandler::Instance().isKeyDown("w")){
		movement += Vector2D(0, -1);

	}

	if(InputHandler::Instance().isKeyDown("s")){
		movement += Vector2D(0, +1);
	}

	if(InputHandler::Instance().isKeyDown("d")){
		movement += Vector2D(1, 0);
	}


	if(InputHandler::Instance().isKeyDown("a")){
		movement += Vector2D(-1, 0);
	}
	movement = movement.norm();
	if(!m_isDashing){
		m_velocity = movement * 2;
	}
		
	dash();

	m_position += m_velocity;
	if(Physics::Instance().checkCollision(this, m_boss)){
		m_position -= m_velocity;
		setLife(m_life - 1);
	}

	for(auto x: engine::Game::Instance().getStateMachine()->currentState()->getShieldObjects()){
		if(Physics::Instance().checkCollision(this, x)){
			if(dynamic_cast<Childmaiden*>(x)->getVisibility())
				m_position -= m_velocity;
			//setLife(m_life - 1);
		}	
	}
}

void Player::useSkill(){

	if(InputHandler::Instance().isKeyDown("1", 200)){
		m_skillManager.setSkillPair(&m_pSkills, RED, &isFirstSkill);
	}

	if(InputHandler::Instance().isKeyDown("2", 200)){
		m_skillManager.setSkillPair(&m_pSkills, GREEN, &isFirstSkill);
	}

	if(InputHandler::Instance().isKeyDown("3", 200)){
		m_skillManager.setSkillPair(&m_pSkills, BLUE, &isFirstSkill);
	}


	if(InputHandler::Instance().isKeyDown("x", 100)){
		std::map<std::pair<default_inks, default_inks>, bool>::iterator it = m_skillManager.getCoolDownMap()->find(m_pSkills);
		if(it != m_skillManager.getCoolDownMap()->end()){
			if(it->second == false){
				m_skillManager.setCoolDownTrigger(m_pSkills);
				if(m_pSkills.first != BLANK and m_pSkills.second != BLANK){
					pixelColors = m_skillManager.getSkill(m_pSkills)();
					TheTextureManager::Instance().changeColorPixels(pixelColors, "bullet");
					TheTextureManager::Instance().changeColorPixels(pixelColors, "instance");
				}
			}
			else
				INFO("TA EM CD");
			
			m_pSkills.first = BLANK;
			m_pSkills.second = BLANK;
			isFirstSkill = true;
		}
	}
}

void Player::dash(){

	if(InputHandler::Instance().isKeyDown("space", 1000)){
		m_dashTime = Timer::Instance().step();
		m_velocity = (m_velocity.norm() * 15);
		m_isDashing = true;
	}

	if(m_isDashing && Timer::Instance().step() >= m_dashTime + 100){
		m_isDashing = false;
	}
	
}

void Player::setPlayerMoves(bool value){
	canMove = value;

}

// void Player::setLife(int life, Uint32 time){
// 	if( m_time == 0){
// 			m_time = Timer::Instance().step() + time;
// 			m_life = life;
// 		}
// 		else if(Timer::Instance().step() <= m_time){
// 			// do nothing
// 		}
// 		else{
// 			m_time = 0;
// 		}
// }
