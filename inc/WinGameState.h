#ifndef WINGAME_STATE_H
#define WINGAME_STATE_H

#include "GameObject.h"
#include "MenuState.h"

#include <string>
#include <vector>

class WinGameState : public MenuState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const {
		return s_winGameID;
	}

	static void s_winGameToMain();
private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static const std::string s_winGameID;
};

#endif
