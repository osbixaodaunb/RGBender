#include "XuxaBoss.h"
#include "Log.h"
#include "Game.h"
#include "Cooldown.h"
#include "PlayState.h"
#include "Childmaiden.h"
#include <iostream>
#include "ChairBullet.h"
#include "Vector2D.h"

using namespace std;
using namespace engine;
bool tilt = false;
bool tilt_chair = false;
bool protection = true;
XuxaBoss::XuxaBoss() : Enemy(){
	m_fireRate = 1;
	TextureManager::Instance().load("assets/bullet.png", "bulletboss", Game::Instance().getRenderer());
	m_states.push_back(&XuxaBoss::quarterLife);
	m_states.push_back(&XuxaBoss::halfLife);
	m_states.push_back(&XuxaBoss::fullLife);
	m_states.back()(); //Deve iniciar/executar o primeiro estado "FULL LIFE"
}

void XuxaBoss::fullLife(){
	INFO("Xuxa está com HP cheio!")
}


void XuxaBoss::halfLife(){
	//TODO
	INFO("Xuxa perdeu metade do HP!")
}

void XuxaBoss::quarterLife(){
	//TODO
	INFO("Xuxa perdeu 3/4 do HP!")
}

void XuxaBoss::load(const LoaderParams* pParams){
	Enemy::load(pParams);
	INFO("Created Xuxa boss");
}

void XuxaBoss::draw(){
	Enemy::draw();
}

void XuxaBoss::update(){
	//std::cout << "Xuxa bottom: " << getPosition().getY() + (getHeight() + getCollider().getHeight())/2 << std::endl;

	if(Game::Instance().getStateMachine()->currentState()->getStateID() == "PLAY"){
		PlayState *playState = dynamic_cast<PlayState*>(Game::Instance().getStateMachine()->currentState());
		if(playState->getLevel() != NULL && m_player == NULL){
			INFO("Player is set");
			m_player = playState->getLevel()->getPlayer();
		}
	}

	if(!tilt){
		//attack();
		tilt = true;
	}
	int half = m_totalHealth / 2;
	int quarter = m_totalHealth / 4;

	if(!tilt_chair and m_actualHealth <= half and m_actualHealth >= quarter){
		throwChair();
		tilt_chair = true;
	}

	Enemy::update();
}

void XuxaBoss::untilt(int placeholder){
	tilt = false;
}

void XuxaBoss::untiltChair(int placeholder){
	tilt_chair = false;
}

void XuxaBoss::protect(int placeholder){
	protection = true;
}

void XuxaBoss::shieldStatus(bool param){
	for(auto x : engine::Game::Instance().getStateMachine()->currentState()->getShieldObjects()){
		dynamic_cast<Childmaiden*>(x)->setVisibility(param);
	}

	
	std::function<void(int)> callback = std::bind(&XuxaBoss::protect, this, 0);
	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(100, callback, 0));
}

void XuxaBoss::attack(){
	Vector2D pos = m_player->getPosition();
	Vector2D playerPivot = Vector2D(m_player->getWidth()/2+pos.getX(), m_player->getHeight()/2 + pos.getY());
	
	pos = getPosition();
	Vector2D bossPivot = Vector2D(getWidth()/2+pos.getX(), getHeight()/2 + pos.getY());

	
	Vector2D velocity = playerPivot - bossPivot;
 	velocity = velocity.norm();
	BossBullet *bullet =  bulletCreator.create(m_player);
	bullet->load(velocity, bossPivot);
	Game::Instance().getStateMachine()->currentState()->addGameObject(bullet);

	std::function<void(int)> callback = std::bind(&XuxaBoss::untilt, this, 0);
	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(250, callback, 0));
}

void XuxaBoss::throwChair(){
	Vector2D pos = m_player->getPosition();
	Vector2D playerPivot = Vector2D(m_player->getWidth()/2+pos.getX(), m_player->getHeight()/2 + pos.getY());
	
	pos = getPosition();
	Vector2D bossPivot = Vector2D(getWidth()/2+pos.getX(), getHeight()/2 + pos.getY());

	
	Vector2D velocity = playerPivot - bossPivot;
 	velocity = velocity.norm();
	ChairBullet *chair =  chairBulletCreator.create(m_player);
	chair->load(velocity, bossPivot);
	Game::Instance().getStateMachine()->currentState()->addGameObject(chair);

	std::function<void(int)> callback = std::bind(&XuxaBoss::untiltChair, this, 0);
	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(3000, callback, 0));
}

void XuxaBoss::clean(){
	Enemy::clean();
}
