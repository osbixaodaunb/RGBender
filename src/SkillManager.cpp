#include "SkillManager.h"
#include "Log.h"
#include "Player.h"
#include "Game.h"
#include "TextureManager.h"

#include <utility>
#include <iostream>
#include <functional>

using namespace engine;

using namespace std;

SkillManager::SkillManager(Player* p_player){
	m_player = p_player;
	TextureManager::Instance().load("assets/red_skill.png", "redskill", Game::Instance().getRenderer());
	TextureManager::Instance().load("assets/green_skill.png", "greenskill", Game::Instance().getRenderer());
	TextureManager::Instance().load("assets/brown_skill.png", "brownskill", Game::Instance().getRenderer());

	m_skills[std::make_pair(RED, RED)] = std::bind(&SkillManager::redPlus, this);
	m_coolDownMap[std::make_pair(RED, RED)] = false;
	m_skills[std::make_pair(GREEN, GREEN)] = std::bind(&SkillManager::greenPlus, this);
	m_coolDownMap[std::make_pair(GREEN, GREEN)] = false;
	m_skills[std::make_pair(BLUE, BLUE)] = std::bind(&SkillManager::bluePlus, this);
	m_coolDownMap[std::make_pair(BLUE, BLUE)] = false;
	m_skills[std::make_pair(BLUE,RED)] = m_skills[std::make_pair(RED, BLUE)] = std::bind(&SkillManager::purple, this);
	m_coolDownMap[std::make_pair(BLUE,RED)] = m_coolDownMap[std::make_pair(RED,BLUE)] = false;
	m_skills[std::make_pair(BLUE,GREEN)] = m_skills[std::make_pair(GREEN, BLUE)] = std::bind(&SkillManager::cyan, this);
	m_coolDownMap[std::make_pair(BLUE,GREEN)] = m_coolDownMap[std::make_pair(GREEN,BLUE)] = false;
	m_skills[std::make_pair(RED,GREEN)] = m_skills[std::make_pair(GREEN, RED)] = std::bind(&SkillManager::brown, this);
	m_coolDownMap[std::make_pair(RED, GREEN)] = m_coolDownMap[std::make_pair(GREEN, RED)] = false;
}

uint8_t* SkillManager::redPlus(){
	INFO("RED PLUS");

	m_player->setFireRate(100);
	std::function<void(int)> redSkill = std::bind(&Player::setFireRate, m_player, 500);
	std::function<void(int)> reset = std::bind(&SkillManager::resetCooldown, this, 1);
	std::function<void(int)> setBlank = std::bind(&SkillManager::blank, this, 255);

	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(1000, redSkill, 500));
	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(1000, setBlank, 255));

	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(5000, reset, 1));

	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 255;
	pixels[1] = 0;
	pixels[2] = 0;
	return pixels;
}

uint8_t* SkillManager::greenPlus(){
	INFO("GREEN PLUS");
	uint8_t* pixels = new uint8_t[3];
	if(m_player->getPlayerBullet() != NULL){
		m_player->getPlayerBullet()->setVenemous(true);
		pixels[0] = 0;
		pixels[1] = 255;
		pixels[2] = 0;
	}else{
		pixels[0] = 255;
		pixels[1] = 255;
		pixels[2] = 255;
	}

	m_player->setFireRate(900);
	std::function<void(int)> redSkill = std::bind(&Player::setFireRate, m_player, 500);

	std::function<void(bool)> greenSkill = std::bind(&Player::setBulletVenemous, m_player, false);
	std::function<void(int)> reset = std::bind(&SkillManager::resetCooldown, this, 2);
	std::function<void(int)> setBlank = std::bind(&SkillManager::blank, this, 255);

	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(3000, redSkill, 500));
	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(3000, greenSkill, false));
	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(3000, setBlank, 255));

	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(3000, reset, 2));

	
	
	return pixels;
}

uint8_t* SkillManager::bluePlus(){
	INFO("BLUE PLUS");
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 0;
	pixels[1] = 0;
	pixels[2] = 255;
	return pixels;
}

uint8_t* SkillManager::purple(){
	INFO("PURPLE PLUS");
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 255;
	pixels[1] = 0;
	pixels[2] = 255;
	return pixels;
}

uint8_t* SkillManager::cyan(){
	INFO("CYAN PLUS");
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 0;
	pixels[1] = 255;
	pixels[2] = 255;
	return pixels;
}

uint8_t* SkillManager::brown(){
	INFO("BROWN PLUS");
	TextureManager::Instance().load("assets/Shield1.png", "shield", Game::Instance().getRenderer());
	//TextureManager::Instance().draw("instance", 100, 600, 100, 100, Game::Instance().getRenderer());

	m_player->setActiveShield(true);

	std::function<void(bool)> brownSkill = std::bind(&Player::setActiveShield, m_player, false);
	std::function<void(int)> reset = std::bind(&SkillManager::resetCooldown, this, 3);
	std::function<void(int)> setBlank = std::bind(&SkillManager::blank, this, 255);

	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(3000, brownSkill, false));
	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(3000, setBlank, 255));

	engine::Game::Instance().addCooldown(new engine::Cooldown<int>(5000, reset, 3));

	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 190;
	pixels[1] = 105;
	pixels[2] = 30;
	return pixels;
}

uint8_t* SkillManager::blank(int placeholder){
	INFO("BLANK");
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 255;
	pixels[1] = 255;
	pixels[2] = 255;

	engine::TextureManager::Instance().changeColorPixels(pixels, "bullet");
	engine::TextureManager::Instance().changeColorPixels(pixels, "instance");

	return pixels;
}


void SkillManager::setSkillPair(std::pair<default_inks, default_inks>* combinedSkills, default_inks ink, bool* isFirst){
	if(combinedSkills->first == BLANK || *isFirst == true){
		combinedSkills->first = ink;
		*isFirst = false;
	}
	else if(combinedSkills->second == BLANK){
		combinedSkills->second = ink;
		*isFirst = true;
	}
}

void SkillManager::resetCooldown(int index){
	// Jeito bem migué de fazer, alguém pensa num jeito melhor ae
	switch(index){
		case 1: m_coolDownMap[make_pair(RED, RED)] = false; break;
		case 2: m_coolDownMap[make_pair(GREEN, GREEN)] = false; break;
		case 3: m_coolDownMap[std::make_pair(RED, GREEN)] = m_coolDownMap[std::make_pair(GREEN, RED)] = false; break;
	}

}

void SkillManager::setCoolDownTrigger(std::pair<default_inks, default_inks> combinedSkills){
	std::cout << combinedSkills.first << '\n';
	std::cout << combinedSkills.second << '\n';

	std::map<std::pair<default_inks, default_inks>, bool>::iterator it = m_coolDownMap.find(combinedSkills);
	if(it == m_coolDownMap.end())
		INFO("NAO ENCONTROU A COMBINACAO")
	else{
		m_coolDownMap[combinedSkills] = true; //Seta a skill pra entrar no estado de CoolDown
	}
}

function<uint8_t*()> SkillManager::getSkill(std::pair<default_inks, default_inks> combinedSkills){
	return m_skills[combinedSkills];
}
