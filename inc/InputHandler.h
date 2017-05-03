#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include <vector>

#include "Vector2D.h"

#define JOYSTICK_DEAD_ZONE 10000

enum mouse_buttons{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler{
public:
	static InputHandler& Instance(){
		static InputHandler instance;

		return instance;
	}

	InputHandler(InputHandler const&) = delete;
	void operator=(InputHandler const&) = delete;

	void update();
	void clean();

	int xvalue(int, int);
	int yvalue(int, int);

	void initialiseJoysticks();
	bool joysticksInitialised(){
		return m_bJoysticksInitialised;
	}

	bool getButtonState(int joy, int buttonNumber){
		return m_buttonStates[joy][buttonNumber];
	}

	Vector2D getMousePosition(){
		return m_mousePosition;
	}

	bool isKeyDown(SDL_Scancode key);
	bool getMouseButtonState(mouse_buttons p_button){
		return m_mouseButtonStates[p_button];
	}
	void reset();

private:
	InputHandler();

	const Uint8* m_keystates;

	Vector2D m_mousePosition;

	std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;

	std::vector<std::vector<bool> > m_buttonStates;

	std::vector<bool> m_mouseButtonStates;

	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialised;

	void onMouseMove(SDL_Event&);
	void onMouseButtonUpDown(SDL_Event&);

	void onJoystickAxisMove(SDL_Event&);
	void onJoystickButtonUpDown(SDL_Event&);
};


#endif
