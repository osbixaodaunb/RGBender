#include "SkillManager.h"

#include <utility>
#include <iostream>

SkillManager::SkillManager(){
	m_skills[std::make_pair(RED, RED)] = &SkillManager::redPlus;
	m_skills[std::make_pair(GREEN, GREEN)] = &SkillManager::greenPlus;
	m_skills[std::make_pair(BLUE, BLUE)] = &SkillManager::bluePlus;
	m_skills[std::make_pair(BLUE,RED)] = m_skills[std::make_pair(RED, BLUE)] = &SkillManager::purple;
	m_skills[std::make_pair(BLUE,GREEN)] = m_skills[std::make_pair(GREEN, BLUE)] = &SkillManager::cyan;
	m_skills[std::make_pair(RED,GREEN)] = m_skills[std::make_pair(GREEN, RED)] = &SkillManager::brown;
}

uint8_t* SkillManager::redPlus(){
	std::cout << "RED PLUS: " << std::endl;
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 255;
	pixels[1] = 0;
	pixels[2] = 0;
	return pixels;
}

uint8_t* SkillManager::greenPlus(){
	std::cout << "GREEN PLUS: " << std::endl;
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 0;
	pixels[1] = 255;
	pixels[2] = 0;
	return pixels;
}

uint8_t* SkillManager::bluePlus(){
	std::cout << "BLUE PLUS: " << std::endl;
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 0;
	pixels[1] = 0;
	pixels[2] = 255;
	return pixels;
}

uint8_t* SkillManager::purple(){
	std::cout << "PURPLE PLUS: " << std::endl;
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 255;
	pixels[1] = 0;
	pixels[2] = 255;
	return pixels;
}

uint8_t* SkillManager::cyan(){
	std::cout << "CYAN PLUS: " << std::endl;
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 0;
	pixels[1] = 255;
	pixels[2] = 255;
	return pixels;
}

uint8_t* SkillManager::brown(){
	std::cout << "BROWN PLUS: " << std::endl;
	uint8_t* pixels = new uint8_t[3];
	pixels[0] = 255;
	pixels[1] = 255;
	pixels[2] = 0;
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

SkillManager::Callback SkillManager::getSkill(std::pair<default_inks, default_inks> combinedSkills){
	return m_skills[combinedSkills];
}