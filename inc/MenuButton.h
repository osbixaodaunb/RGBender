#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "BaseCreator.h"

class MenuButton : public SDLGameObject{
public:
	MenuButton();

	void load(const LoaderParams* pParams);

	void setCallback(void(*callback) ()) {
		m_callback = callback;
	}

	int getCallbackID(){
		return m_callbackID;
	}

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	enum button_state{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void (*m_callback) ();
	bool m_bReleased;
	int m_callbackID;
};

class MenuButtonCreator : public BaseCreator{
	GameObject* createGameObject() const{
		return new MenuButton();
	}
};
#endif
