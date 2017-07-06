/*#include "ShieldSkill.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"

using namespace engine;


ShieldSkill::~ShieldSkill(){
	m_active = true;
	
}
ShieldSkill::ShieldSkill() : SDLGameObject(){

}

void ShieldSkill::load(const LoaderParams* pParams){
	//m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}


void ShieldSkill::load(Vector2D pVelocity, Vector2D pPosition){

	//m_moveSpeed = 5;
	LoaderParams* pParams = new LoaderParams(pPosition.getX(), pPosition.getY(), 16, 16, "ShieldSkill", 0, 0, 0, angle);
	SDLGameObject::load(pParams);

	//m_currentFrame = 0;
	//bornTime = Timer::Instance().step();
	//m_velocity = pVelocity.norm() * m_moveSpeed;
}

void ShieldSkill::draw(){
	SDLGameObject::draw();
}

void ShieldSkill::update(){
	//std::cout << "PlayerShield top: " << getPosition().getY() + (getHeight() - getCollider().getHeight())/2 << std::endl;
	//m_position += m_velocity;
	INFO("OIOIOIOIOIO");
	if(Game::Instance().getStateMachine()->currentState()->getStateID() == "PLAY"){
		PlayState *playState = dynamic_cast<PlayState*>(Game::Instance().getStateMachine()->currentState());
		if(playState->getLevel() != NULL && m_boss == NULL){
			INFO("Xuxa is set");
			m_boss = playState->getLevel()->getXuxa();
		}
	}
	//m_position = m_player->getPosition();
	
	checkCollision();

	if(numberHits > 5){
		m_active = false;
		Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
	}ded = false;


}

void ShieldSkill::checkCollision(){
	if(m_active){
		//Vector2D bossPos = m_player->getBoss()->getPosition();
		//Vector2D thisPos = getPosition();
		
		if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(m_boss), dynamic_cast<SDLGameObject*>(this))){
			numberHits++;
			// if(m_venemous){
			// 	INFO("VENEMOUS TRUE");
			// 	m_collided = true;
			// 	m_boss->setEnemyTime(300);
			// }
			
			//int score = Game::Instance().getScore();
			//Game::Instance().setScore(score + 10);
			//TextureManager::Instance().loadText(std::to_string(Game::Instance().getScore()), "assets/fonts/Lato-Regular.ttf", "score", {255,255,255}, 50, Game::Instance().getRenderer());
			INFO("PlayerShield collided with the boss");
		}
		if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(m_boss->getBossBullet(), dynamic_cast<SDLGameObject*>(this)))){
			numberHits++;
			INFO("PlayerShield collided with boss bullet");
		}
	}
}

void ShieldSkill::clean(){
	SDLGameObject::clean();
}*/