#ifndef GAMEOVER_STATE_H
#define GAMEOVER_STATE_H

#include "MenuState.h"

#include <string>
#include <vector>

class GameOverState : public MenuState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const {
		return s_gameOverID;
	}

private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_gameOverToMain();
	static void s_restartPlay();

	static const std::string s_gameOverID;
};

#endif
