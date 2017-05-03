#include "MenuButton.h"
#include "Vector2D.h"
#include "InputHandler.h"

MenuButton::MenuButton() : SDLGameObject(){
}

void MenuButton::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);

	m_callbackID = pParams->getCallbackID();

	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw(){
	SDLGameObject::draw();
}

void MenuButton::update(){
	Vector2D pMousePos = InputHandler::Instance().getMousePosition();

	if(pMousePos.getX() < (m_position.getX() + m_width)
		and pMousePos.getX() > m_position.getX()
		and pMousePos.getY() < (m_position.getY() + m_height)
		and pMousePos.getY() > m_position.getY()){

		if(InputHandler::Instance().getMouseButtonState(LEFT) && m_bReleased){
			m_currentFrame = CLICKED;

			m_callback();

			m_bReleased = false;
		} else if(!InputHandler::Instance().getMouseButtonState(LEFT)){
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	} else {
		m_currentFrame = MOUSE_OUT;		
	}
}

void MenuButton::clean(){
	SDLGameObject::clean();
}

