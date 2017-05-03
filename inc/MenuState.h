#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"

#include <vector>

class MenuState : public GameState{
public:
	typedef void(*Callback) ();
protected:
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
	std::vector<Callback> m_callbacks;
};

#endif
