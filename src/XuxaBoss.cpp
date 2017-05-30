#include "XuxaBoss.h"
#include "Log.h"
#include "Game.h"
#include "PlayState.h"

using namespace engine;
bool tilt = false;
XuxaBoss::XuxaBoss() : Enemy(){
	m_fireRate = 1;
	TextureManager::Instance().load("assets/clash2.png", "bulletboss", Game::Instance().getRenderer());
	m_states.push_back(&XuxaBoss::quarterLife);
	m_states.push_back(&XuxaBoss::halfLife);
	m_states.push_back(&XuxaBoss::fullLife);
	m_states.back()(); //Deve iniciar/executar o primeiro estado "FULL LIFE"
}

void XuxaBoss::fullLife(){
	//TODO
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

	if(Game::Instance().getStateMachine()->currentState()->getStateID() == "PLAY"){
		PlayState *playState = dynamic_cast<PlayState*>(Game::Instance().getStateMachine()->currentState());
		if(playState->getLevel() != NULL && m_player == NULL){
			INFO("Player is set");
			m_player = playState->getLevel()->getPlayer();
		}
	}

	if(!tilt){
		attack();
		tilt = true;
	}

	Enemy::update();
}

void XuxaBoss::attack(){
	//Vector2D pivot = Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY());
	Vector2D target = m_player->getPosition();
	target = target.norm();
	BossBullet *bullet =  bulletCreator.create(m_player);
	bullet->load(target, Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY()));
	Game::Instance().getStateMachine()->currentState()->addGameObject(bullet);
}

void XuxaBoss::clean(){
	Enemy::clean();
}