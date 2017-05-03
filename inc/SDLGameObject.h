#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Vector2D.h"

#include <string>

class SDLGameObject : public GameObject{
public:
	SDLGameObject();

	virtual void load(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	std::string getTextureID(){
		return m_textureID;
	}

	Vector2D& getPosition() {
		return m_position;
	}

	int getWidth(){
		return m_width;
	}

	int getHeight(){
		return m_height;
	}

protected:

	Vector2D m_position;	
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;

	int m_numFrames;

	std::string m_textureID;

};

#endif
