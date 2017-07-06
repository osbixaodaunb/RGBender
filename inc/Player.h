#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"
#include "SkillManager.h"
#include "Timer.h"
#include "Bullet.h"

#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Enemy;

class Player : public engine::SDLGameObject{
public:
	Player();

	void changeSprite(int);
	void load(const engine::LoaderParams* pParams);
	void draw();
	void update();
	void clean();
	typedef uint8_t*(*Callback) ();
	uint8_t* pixelColors;
	void setFireRate(int fireRate){
		m_fireRate = fireRate;
	}
	void setLife(int life){
		m_life = life;
	}
	int getLife(){
		return m_life;
	}
	Bullet* getPlayerBullet(){
		return bullet;
	}
	void setShieldHits(){
		shieldHits++;
	}
	int getShieldHits(){
		return shieldHits;
	}
	void setActiveShield(bool isActive){
		m_isShieldActive = isActive;
	}
	bool getShieldActive(){
		return m_isShieldActive;
	}
	void setBulletVenemous(bool isVenemous);
	void setPoison();
	void setPlayerMoves(bool);
	int setStunTime(int value){
		stunTime = value;
	}

	int getStunTime(){
		return stunTime;
	}
private:
	Bullet *bullet = NULL;
	bool m_isShieldActive;
	int shieldHits = 0;
	bool m_bulletVenemous = false;
	int count = 0;
	void handleInput();
	SkillManager m_skillManager = SkillManager(this);
	std::pair<default_inks, default_inks> m_pSkills;
	bool isFirstSkill = true;
	void move();
	void rotateTowards();
	void dash();
	void useSkill();
	bool canMove;
	int stunTime;
	int m_life;
	Uint32 m_time;
	bool m_isDashing;
	Uint32 m_dashTime;
	int m_fireRate;
	BulletCreator bulletCreator;

	Enemy* m_boss = NULL;
};

class PlayerCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new Player();
	}
};

#endif
