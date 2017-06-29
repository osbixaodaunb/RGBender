#include "XuxaBoss.h"
#include "Log.h"
#include "Game.h"
#include "Cooldown.h"
#include "PlayState.h"

using namespace engine;
bool tilt = false;
XuxaBoss::XuxaBoss() : Enemy(){
	m_fireRate = 1;
	TextureManager::Instance().load("assets/bullet.png", "bulletboss", Game::Instance().getRenderer());
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
	std::cout << "Xuxa bottom: " << getPosition().getY() + (getHeight() + getCollider().getHeight())/2 << std::endl;

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

void XuxaBoss::untilt(int placeholder){
	tilt = false;
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

void XuxaBoss::clean(){
	Enemy::clean();
}
