#ifndef __SKILLMANAGER__
#define __SKILLMANAGER__

#include <stdint.h>
#include <map>

enum default_inks{
	BLANK = 0,
	RED = 1,
	GREEN = 2,
	BLUE = 3
};

class SkillManager{

public:
	SkillManager();
	typedef uint8_t*(*Callback) ();
	void setSkillPair(std::pair<default_inks, default_inks>* combinedSkills, 
		default_inks, bool* isFirst);
	Callback getSkill(std::pair<default_inks, default_inks> combinedSkills);
	void setCoolDownTrigger(std::pair<default_inks, default_inks> combinedSkills);
	void setCoolDownTimer(std::pair<default_inks, default_inks> combinedSkills);
	std::map<std::pair<default_inks, default_inks>, bool>* getCoolDownMap(){
		return &m_coolDownMap;
	}
private:

	static uint8_t* purple();
	static uint8_t* brown();
	static uint8_t* cyan();
	static uint8_t* redPlus();
	static uint8_t* greenPlus();
	static uint8_t* bluePlus();
	std::map<std::pair<default_inks, default_inks>, Callback> m_skills;
	std::map<std::pair<default_inks, default_inks>, bool> m_coolDownMap;

};

#endif