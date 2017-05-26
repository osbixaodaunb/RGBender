#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "MenuState.h"

#include <vector>
#include <string>

class MainMenuState : public MenuState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const {
		return s_menuID;
	}

private:
	void setCallbacks(const std::vector<Callback> &callbacks);

	static void s_menuToPlay();
	static void s_exitFromMenu();

	static const std::string s_menuID;
};


#endif
