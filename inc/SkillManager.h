#ifndef __SKILLMANAGER__
#define __SKILLMANAGER__

#include <stdint.h>
#include <map>
#include <functional>

class Player;

enum default_inks{
	BLANK = 0,
	RED = 1,
	GREEN = 2,
	BLUE = 3
};

class SkillManager{

public:
	SkillManager(Player *p_Player);

	void setSkillPair(std::pair<default_inks, default_inks>* combinedSkills, default_inks, bool* isFirst);

	std::function<uint8_t*()> getSkill(std::pair<default_inks, default_inks> combinedSkills);

	void setCoolDownTrigger(std::pair<default_inks, default_inks> combinedSkills);

	void resetCooldown(int);

	std::map<std::pair<default_inks, default_inks>, bool>* getCoolDownMap(){
		return &m_coolDownMap;
	}
private:
	Player *m_player;

	uint8_t* purple();
	uint8_t* brown();
	uint8_t* cyan();
	uint8_t* redPlus();
	uint8_t* greenPlus();
	uint8_t* bluePlus();
	uint8_t* blank(int);

	std::map<std::pair<default_inks, default_inks>, std::function< uint8_t*()> > m_skills;
	std::map<std::pair<default_inks, default_inks>, bool> m_coolDownMap;

};

#endif
