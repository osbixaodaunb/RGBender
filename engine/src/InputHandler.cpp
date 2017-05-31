#include "InputHandler.h"

#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "Log.h"
using namespace std;
using namespace engine;

InputHandler::InputHandler(){
	create_keyboard_mapping();
	for(int i=0; i<3; i++){
		m_mouseButtonStates.push_back(false);
	}
}

void InputHandler::initialiseJoysticks(){
	if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if(SDL_NumJoysticks() > 0){
		for(int i = 0; i < SDL_NumJoysticks(); i++){
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if(joy){
				m_joysticks.push_back(joy);
				m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0, 0)));

				std::vector<bool> tempButtons;
				for(int j = 0; j < SDL_JoystickNumButtons(joy); j++){
					tempButtons.push_back(false);
				}

				m_buttonStates.push_back(tempButtons);
			} else {
				cout << SDL_GetError();			
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		INFO("Initialised joysticks: " + m_joysticks.size());
	} else {
		m_bJoysticksInitialised = false;
	}
}

void InputHandler::clean(){
	if(m_bJoysticksInitialised){
		for(unsigned int i=0; i < m_joysticks.size(); ++i){
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

void InputHandler::update(){
	SDL_Event event;

	m_keystates = SDL_GetKeyboardState(0);
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				Game::Instance().quit();
			break;

			case SDL_JOYAXISMOTION:
				onJoystickAxisMove(event);
			break;

			case SDL_JOYBUTTONDOWN:

			case SDL_JOYBUTTONUP:
				onJoystickButtonUpDown(event);
			break;

			case SDL_MOUSEMOTION:
				onMouseMove(event);
			break;

			case SDL_MOUSEBUTTONDOWN:

			case SDL_MOUSEBUTTONUP:
				onMouseButtonUpDown(event);
			break;
		}
	}
}

int InputHandler::xvalue(int joy, int stick){
	if(m_joystickValues.size() > 0){
		if(stick == 1){
			return m_joystickValues[joy].first->getX();
		} else if(stick == 2){
			return m_joystickValues[joy].second->getX();
		}
	}

	return 0;
}

int InputHandler::yvalue(int joy, int stick){
	if(m_joystickValues.size() > 0){
		if(stick == 1){
			return m_joystickValues[joy].first->getY();
		} else if (stick == 2){
			return m_joystickValues[joy].second->getY();
		}
	}

	return 0;
}

bool InputHandler::isKeyDown(const std::string & key){
	if(m_keystates != 0){
		return m_keystates[m_buttons[key]] == 1;
	}

	return false;
}

bool InputHandler::isKeyDown(const std::string & key, Uint32 time){

	if(m_keystates != 0){
		if(m_keystates[m_buttons[key]] == 1 ){
			if(m_times[m_buttons[key]] == 0){
				m_times[m_buttons[key]] = Timer::Instance().step() + time;
				return true;
			} else if(Timer::Instance().step() <= m_times[m_buttons[key]]){
				return false;
			} else {
				m_times[m_buttons[key]] = 0;
			}
		}
	}

	return false;
}

void InputHandler::onJoystickAxisMove(SDL_Event &event){
	if(event.type == SDL_JOYAXISMOTION){
		int whichOne = event.jaxis.which;
		// left stick move left or right
		if(event.jaxis.axis == 0) {
			if (event.jaxis.value > JOYSTICK_DEAD_ZONE) {
				m_joystickValues[whichOne].first->setX(1);
			} else if(event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
				m_joystickValues[whichOne].first->setX(-1);
			} else {
				m_joystickValues[whichOne].first->setX(0);
			}
		}

		// left stick move up or down
		if(event.jaxis.axis == 1) {
			if (event.jaxis.value > JOYSTICK_DEAD_ZONE) {
				m_joystickValues[whichOne].first->setY(1);
			} else if(event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
				m_joystickValues[whichOne].first->setY(-1);
			} else {
				m_joystickValues[whichOne].first->setY(0);
			}
		}
	}
}

void InputHandler::onJoystickButtonUpDown(SDL_Event& event){
	if(event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP){
		int whichOne = event.jaxis.which;
	
		m_buttonStates[whichOne][event.jbutton.button] = event.type == SDL_JOYBUTTONDOWN;
	}
}

void InputHandler::onMouseButtonUpDown(SDL_Event& event){
	int buttonTypes[] {SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT};

	for(int i=0; i<3; i++){
		if(event.button.button == buttonTypes[i]){
			m_mouseButtonStates[i] = event.type == SDL_MOUSEBUTTONDOWN;
		}
	}
}

void InputHandler::onMouseMove(SDL_Event& event){
	if(event.type == SDL_MOUSEMOTION){
		m_mousePosition.setX(event.motion.x);
		m_mousePosition.setY(event.motion.y);
	}
}	

void InputHandler::reset(){
	for(auto mouseButton : m_mouseButtonStates){
		mouseButton = false;
	}
}

void InputHandler::create_keyboard_mapping(){
    m_buttons["unknown"] = SDL_SCANCODE_UNKNOWN;
    m_buttons["enter"] = SDL_SCANCODE_RETURN;
    m_buttons["esc"] = SDL_SCANCODE_ESCAPE;
    m_buttons["backspace"] = SDL_SCANCODE_BACKSPACE;
    m_buttons["tab"] = SDL_SCANCODE_TAB;
    m_buttons["space"] = SDL_SCANCODE_SPACE;
    m_buttons["0"] = SDL_SCANCODE_0;
    m_buttons["1"] = SDL_SCANCODE_1;
    m_buttons["2"] = SDL_SCANCODE_2;
    m_buttons["3"] = SDL_SCANCODE_3;
    m_buttons["4"] = SDL_SCANCODE_4;
    m_buttons["5"] = SDL_SCANCODE_5;
    m_buttons["6"] = SDL_SCANCODE_6;
    m_buttons["7"] = SDL_SCANCODE_7;
    m_buttons["8"] = SDL_SCANCODE_8;
    m_buttons["9"] = SDL_SCANCODE_9;
    m_buttons[";"] = SDL_SCANCODE_SEMICOLON;
    m_buttons["="] = SDL_SCANCODE_EQUALS;

    m_buttons["["] = SDL_SCANCODE_LEFTBRACKET;
    m_buttons["\\"] = SDL_SCANCODE_BACKSLASH;
    m_buttons["]"] = SDL_SCANCODE_RIGHTBRACKET;
    m_buttons["a"] = SDL_SCANCODE_A;
    m_buttons["b"] = SDL_SCANCODE_B;
    m_buttons["c"] = SDL_SCANCODE_C;
    m_buttons["d"] = SDL_SCANCODE_D;
    m_buttons["e"] = SDL_SCANCODE_E;
    m_buttons["f"] = SDL_SCANCODE_F;
    m_buttons["g"] = SDL_SCANCODE_G;
    m_buttons["h"] = SDL_SCANCODE_H;
    m_buttons["i"] = SDL_SCANCODE_I;
    m_buttons["j"] = SDL_SCANCODE_J;
    m_buttons["k"] = SDL_SCANCODE_K;
    m_buttons["l"] = SDL_SCANCODE_L;
    m_buttons["m"] = SDL_SCANCODE_M;
    m_buttons["n"] = SDL_SCANCODE_N;
    m_buttons["o"] = SDL_SCANCODE_O;
    m_buttons["p"] = SDL_SCANCODE_P;
    m_buttons["q"] = SDL_SCANCODE_Q;
    m_buttons["r"] = SDL_SCANCODE_R;
    m_buttons["s"] = SDL_SCANCODE_S;
    m_buttons["t"] = SDL_SCANCODE_T;
    m_buttons["u"] = SDL_SCANCODE_U;
    m_buttons["v"] = SDL_SCANCODE_V;
    m_buttons["w"] = SDL_SCANCODE_W;
    m_buttons["x"] = SDL_SCANCODE_X;
    m_buttons["y"] = SDL_SCANCODE_Y;
    m_buttons["z"] = SDL_SCANCODE_Z	;

    m_buttons["capslock"] = SDL_SCANCODE_CAPSLOCK;

    m_buttons["f1"] = SDL_SCANCODE_F1;
    m_buttons["f2"] = SDL_SCANCODE_F2;
    m_buttons["f3"] = SDL_SCANCODE_F3;
    m_buttons["f4"] = SDL_SCANCODE_F4;
    m_buttons["f5"] = SDL_SCANCODE_F5;
    m_buttons["f6"] = SDL_SCANCODE_F6;
    m_buttons["f7"] = SDL_SCANCODE_F7;
    m_buttons["f8"] = SDL_SCANCODE_F8;
    m_buttons["f9"] = SDL_SCANCODE_F9;
    m_buttons["f10"] = SDL_SCANCODE_F10;
    m_buttons["f11"] = SDL_SCANCODE_F11;
    m_buttons["f12"] = SDL_SCANCODE_F12;

    m_buttons["printscreen"] = SDL_SCANCODE_PRINTSCREEN;
    m_buttons["scrolllock"] = SDL_SCANCODE_SCROLLLOCK;
    m_buttons["pause"] = SDL_SCANCODE_PAUSE;
    m_buttons["insert"] = SDL_SCANCODE_INSERT;
    m_buttons["home"] = SDL_SCANCODE_HOME;
    m_buttons["pageup"] = SDL_SCANCODE_PAGEUP;
    m_buttons["delete"] = SDL_SCANCODE_DELETE;
    m_buttons["end"] = SDL_SCANCODE_END;
    m_buttons["pagedown"] = SDL_SCANCODE_PAGEDOWN;
    m_buttons["right"] = SDL_SCANCODE_RIGHT;
    m_buttons["left"] = SDL_SCANCODE_LEFT;
    m_buttons["down"] = SDL_SCANCODE_DOWN;
    m_buttons["up"] = SDL_SCANCODE_UP;

    m_buttons["numlock"] = SDL_SCANCODE_NUMLOCKCLEAR;
    m_buttons["key pad /"] = SDL_SCANCODE_KP_DIVIDE;
    m_buttons["key pad *"] = SDL_SCANCODE_KP_MULTIPLY;
    m_buttons["key pad -"] = SDL_SCANCODE_KP_MINUS;
    m_buttons["key pad +"] = SDL_SCANCODE_KP_PLUS;
    m_buttons["key pad enter"] = SDL_SCANCODE_KP_ENTER;
    m_buttons["key pad 1"] = SDL_SCANCODE_KP_1;
    m_buttons["key pad 2"] = SDL_SCANCODE_KP_2;
    m_buttons["key pad 3"] = SDL_SCANCODE_KP_3;
    m_buttons["key pad 4"] = SDL_SCANCODE_KP_4;
    m_buttons["key pad 5"] = SDL_SCANCODE_KP_5;
    m_buttons["key pad 6"] = SDL_SCANCODE_KP_6;
    m_buttons["key pad 7"] = SDL_SCANCODE_KP_7;
    m_buttons["key pad 8"] = SDL_SCANCODE_KP_8;
    m_buttons["key pad 9"] = SDL_SCANCODE_KP_9;
    m_buttons["key pad 0"] = SDL_SCANCODE_KP_0;
    m_buttons["key pad ."] = SDL_SCANCODE_KP_PERIOD;

    m_buttons["application"] = SDL_SCANCODE_APPLICATION;
    m_buttons["power"] = SDL_SCANCODE_POWER;
    m_buttons["key pad ="] = SDL_SCANCODE_KP_EQUALS;
    m_buttons["f13"] = SDL_SCANCODE_F13;
    m_buttons["f14"] = SDL_SCANCODE_F14;
    m_buttons["f15"] = SDL_SCANCODE_F15;
    m_buttons["f16"] = SDL_SCANCODE_F16;
    m_buttons["f17"] = SDL_SCANCODE_F17;
    m_buttons["f18"] = SDL_SCANCODE_F18;
    m_buttons["f19"] = SDL_SCANCODE_F19;
    m_buttons["f20"] = SDL_SCANCODE_F20;
    m_buttons["f21"] = SDL_SCANCODE_F21;
    m_buttons["f22"] = SDL_SCANCODE_F22;
    m_buttons["f23"] = SDL_SCANCODE_F23;
    m_buttons["f24"] = SDL_SCANCODE_F24;
    m_buttons["execute"] = SDL_SCANCODE_EXECUTE;
    m_buttons["help"] = SDL_SCANCODE_HELP;
    m_buttons["menu"] = SDL_SCANCODE_MENU;
    m_buttons["select"] = SDL_SCANCODE_SELECT;
    m_buttons["stop"] = SDL_SCANCODE_STOP;
    m_buttons["again"] = SDL_SCANCODE_AGAIN;
    m_buttons["undo"] = SDL_SCANCODE_UNDO;
    m_buttons["cut"] = SDL_SCANCODE_CUT;
    m_buttons["copy"] = SDL_SCANCODE_COPY;
    m_buttons["paste"] = SDL_SCANCODE_PASTE;
    m_buttons["find"] = SDL_SCANCODE_FIND;
    m_buttons["mute"] = SDL_SCANCODE_MUTE;
    m_buttons["volumeuP"] = SDL_SCANCODE_VOLUMEUP;
    m_buttons["volumedown"] = SDL_SCANCODE_VOLUMEDOWN;
    m_buttons["key pad ,"] = SDL_SCANCODE_KP_COMMA;
    m_buttons["key pad equalsas400"] = SDL_SCANCODE_KP_EQUALSAS400;

    m_buttons["alterase"] = SDL_SCANCODE_ALTERASE;
    m_buttons["sysreq"] = SDL_SCANCODE_SYSREQ;
    m_buttons["cancel"] = SDL_SCANCODE_CANCEL;
    m_buttons["clear"] = SDL_SCANCODE_CLEAR;
    m_buttons["prior"] = SDL_SCANCODE_PRIOR;
    m_buttons["return2"] = SDL_SCANCODE_RETURN2;
    m_buttons["separator"] = SDL_SCANCODE_SEPARATOR;
    m_buttons["out"] = SDL_SCANCODE_OUT;
    m_buttons["oper"] = SDL_SCANCODE_OPER;
    m_buttons["clearagain"] = SDL_SCANCODE_CLEARAGAIN;
    m_buttons["crsel"] = SDL_SCANCODE_CRSEL;
    m_buttons["exsel"] = SDL_SCANCODE_EXSEL;

    m_buttons["key pad 00"] = SDL_SCANCODE_KP_00;
    m_buttons["key pad 000"] = SDL_SCANCODE_KP_000;
    m_buttons["thousandsseparator"] = SDL_SCANCODE_THOUSANDSSEPARATOR;
    m_buttons["decimalseparator"] = SDL_SCANCODE_DECIMALSEPARATOR;
    m_buttons["currencyunit"] = SDL_SCANCODE_CURRENCYUNIT;
    m_buttons["currencysubunit"] = SDL_SCANCODE_CURRENCYSUBUNIT;
    m_buttons["key pad ("] = SDL_SCANCODE_KP_LEFTPAREN;
    m_buttons["key pad )"] = SDL_SCANCODE_KP_RIGHTPAREN;
    m_buttons["key pad {"] = SDL_SCANCODE_KP_LEFTBRACE;
    m_buttons["key pad }"] = SDL_SCANCODE_KP_RIGHTBRACE;
    m_buttons["key pad tab"] = SDL_SCANCODE_KP_TAB;
    m_buttons["key pad backspace"] = SDL_SCANCODE_KP_BACKSPACE;
    m_buttons["key pad a"] = SDL_SCANCODE_KP_A;
    m_buttons["key pad b"] = SDL_SCANCODE_KP_B;
    m_buttons["key pad c"] = SDL_SCANCODE_KP_C;
    m_buttons["key pad d"] = SDL_SCANCODE_KP_D;
    m_buttons["key pad e"] = SDL_SCANCODE_KP_E;
    m_buttons["key pad f"] = SDL_SCANCODE_KP_F;
    m_buttons["key pad xor"] = SDL_SCANCODE_KP_XOR;
    m_buttons["key pad power"] = SDL_SCANCODE_KP_POWER;
    m_buttons["key pad %"] = SDL_SCANCODE_KP_PERCENT;
    m_buttons["key pad <"] = SDL_SCANCODE_KP_LESS;
    m_buttons["key pad >"] = SDL_SCANCODE_KP_GREATER;
    m_buttons["key pad &"] = SDL_SCANCODE_KP_AMPERSAND;
    m_buttons["key pad &&"] = SDL_SCANCODE_KP_DBLAMPERSAND;
    m_buttons["key pad |"] = SDL_SCANCODE_KP_VERTICALBAR;
    m_buttons["key pad ||"] = SDL_SCANCODE_KP_DBLVERTICALBAR;
    m_buttons["key pad :"] = SDL_SCANCODE_KP_COLON;
    m_buttons["key pad #"] = SDL_SCANCODE_KP_HASH;
    m_buttons["key pad space"] = SDL_SCANCODE_KP_SPACE;
    m_buttons["key pad @"] = SDL_SCANCODE_KP_AT;
    m_buttons["key pad !"] = SDL_SCANCODE_KP_EXCLAM;
    m_buttons["key pad memstore"] = SDL_SCANCODE_KP_MEMSTORE;
    m_buttons["key pad memrecall"] = SDL_SCANCODE_KP_MEMRECALL;
    m_buttons["key pad memclear"] = SDL_SCANCODE_KP_MEMCLEAR;
    m_buttons["key pad memadd"] = SDL_SCANCODE_KP_MEMADD;
    m_buttons["key pad memsubtract"] = SDL_SCANCODE_KP_MEMSUBTRACT;
    m_buttons["key pad memmultiply"] = SDL_SCANCODE_KP_MEMMULTIPLY;
    m_buttons["key pad memdivide"] = SDL_SCANCODE_KP_MEMDIVIDE;
    m_buttons["key pad plusminus"] = SDL_SCANCODE_KP_PLUSMINUS;
    m_buttons["key pad clear"] = SDL_SCANCODE_KP_CLEAR;
    m_buttons["key pad clearentry"] = SDL_SCANCODE_KP_CLEARENTRY;
    m_buttons["key pad binary"] = SDL_SCANCODE_KP_BINARY;
    m_buttons["key pad octal"] = SDL_SCANCODE_KP_OCTAL;
    m_buttons["key pad decimal"] = SDL_SCANCODE_KP_DECIMAL;
    m_buttons["key pad hexadecimal"] = SDL_SCANCODE_KP_HEXADECIMAL;

    m_buttons["left ctrl"] = SDL_SCANCODE_LCTRL;
    m_buttons["left shift"] = SDL_SCANCODE_LSHIFT;
    m_buttons["left alt"] = SDL_SCANCODE_LALT;
    m_buttons["left gui"] = SDL_SCANCODE_LGUI;
    m_buttons["right ctrl"] = SDL_SCANCODE_RCTRL;
    m_buttons["right shift"] = SDL_SCANCODE_RSHIFT;
    m_buttons["right alt"] = SDL_SCANCODE_RALT;
    m_buttons["right gui"] = SDL_SCANCODE_RGUI;

    m_buttons["mode"] = SDL_SCANCODE_MODE;

    m_buttons["audio next"] = SDL_SCANCODE_AUDIONEXT;
    m_buttons["audio prev"] = SDL_SCANCODE_AUDIOPREV;
    m_buttons["audio stop"] = SDL_SCANCODE_AUDIOSTOP;
    m_buttons["audio play"] = SDL_SCANCODE_AUDIOPLAY;
    m_buttons["audio mute"] = SDL_SCANCODE_AUDIOMUTE;
    m_buttons["media select"] = SDL_SCANCODE_MEDIASELECT;
    m_buttons["www"] = SDL_SCANCODE_WWW;
    m_buttons["mail"] = SDL_SCANCODE_MAIL;
    m_buttons["calculator"] = SDL_SCANCODE_CALCULATOR;
    m_buttons["computer"] = SDL_SCANCODE_COMPUTER;
    m_buttons["ac_search"] = SDL_SCANCODE_AC_SEARCH;
    m_buttons["ac_home"] = SDL_SCANCODE_AC_HOME;
    m_buttons["ac_back"] = SDL_SCANCODE_AC_BACK;
    m_buttons["ac_forward"] = SDL_SCANCODE_AC_FORWARD;
    m_buttons["ac_stop"] = SDL_SCANCODE_AC_STOP;
    m_buttons["ac_refresh"] = SDL_SCANCODE_AC_REFRESH;
    m_buttons["ac_bookmarks"] = SDL_SCANCODE_AC_BOOKMARKS;

    m_buttons["brightness down"] = SDL_SCANCODE_BRIGHTNESSDOWN;
    m_buttons["brightness up"] = SDL_SCANCODE_BRIGHTNESSUP;
    m_buttons["displayswitch"] = SDL_SCANCODE_DISPLAYSWITCH;
    m_buttons["kbdillumtoggle"] = SDL_SCANCODE_KBDILLUMTOGGLE;
    m_buttons["kbdillumdown"] = SDL_SCANCODE_KBDILLUMDOWN;
    m_buttons["kbdillumup"] = SDL_SCANCODE_KBDILLUMUP;
    m_buttons["eject"] = SDL_SCANCODE_EJECT;
    m_buttons["sleep"] = SDL_SCANCODE_SLEEP;

}