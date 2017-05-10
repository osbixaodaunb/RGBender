#include "SkillManager.h"

#include <utility>
#include <iostream>

SkillManager::SkillManager(){
	m_skills[std::make_pair(RED, RED)] = &SkillManager::redPlus;
	m_coolDownMap[std::make_pair(RED, RED)] = false;
	m_skills[std::make_pair(GREEN, GREEN)] = &SkillManager::greenPlus;
	m_coolDownMap[std::make_pair(GREEN, GREEN)] = false;
	m_skills[std::make_pair(BLUE, BLUE)] = &SkillManager::bluePlus;
	m_coolDownMap[std::make_pair(BLUE, BLUE)] = false;
	m_skills[std::make_pair(BLUE,RED)] = m_skills[std::make_pair(RED, BLUE)] = &SkillManager::purple;
	m_coolDownMap[std::make_pair(BLUE,RED)] = m_coolDownMap[std::make_pair(RED,BLUE)] = false;
	m_skills[std::make_pair(BLUE,GREEN)] = m_skills[std::make_pair(GREEN, BLUE)] = &SkillManager::cyan;
	m_coolDownMap[std::make_pair(BLUE,GREEN)] = m_coolDownMap[std::make_pair(GREEN,BLUE)] = false;
	m_skills[std::make_pair(RED,GREEN)] = m_skills[std::make_pair(GREEN, RED)] = &SkillManager::brown;
	m_coolDownMap[std::make_pair(RED, GREEN)] = m_coolDownMap[std::make_pair(GREEN, RED)] = false;
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
	pixels[0] = 190;
	pixels[1] = 105;
	pixels[2] = 30;
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

void SkillManager::setCoolDownTimer(std::pair<default_inks, default_inks> combinedSkills){
	/*Todo: Pensar como fazer cooldown generico, inves de criar funcao de CD pra cada uma
	 to mt cansado agora, pra achar uma boa solucao*/
	// Esse metodo é pra lidar com o tempo de CD pra resetar o cooldown.
}

void SkillManager::setCoolDownTrigger(std::pair<default_inks, default_inks> combinedSkills){
	std::cout << combinedSkills.first << '\n';
	std::cout << combinedSkills.second << '\n';

	std::map<std::pair<default_inks, default_inks>, bool>::iterator it = m_coolDownMap.find(combinedSkills);
	if(it == m_coolDownMap.end())
		std::cout << "NAO ENCONTROU A COMBINACAO\n";
	else{
		m_coolDownMap[combinedSkills] = true; //Seta a skill pra entrar no estado de CoolDown
	}
}

SkillManager::Callback SkillManager::getSkill(std::pair<default_inks, default_inks> combinedSkills){
	return m_skills[combinedSkills];
}