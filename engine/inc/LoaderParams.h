#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H

#include <string>
#include <iostream>

#include "Vector2D.h"
#include "Collider.h"

namespace engine{

	class LoaderParams{
	public:
		LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0, double angle = 0, int colliderWidth = 10, int colliderHeight = 10) : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_numFrames(numFrames), m_callbackID(callbackID), m_animSpeed(animSpeed), m_angle(angle){
			Vector2D center = Vector2D(m_x + width/2, m_y + height/2);
			m_collider = Collider(center, colliderWidth, colliderHeight);
		}

		int getX() const {
			return m_x;
		}

		int getY() const {
			return m_y;
		}

		int getWidth() const {
			return m_width;
		}

		int getHeight() const {
			return m_height;
		}

		std::string getTextureID() const {
			return m_textureID;
		}

		int getNumFrames() const{
			return m_numFrames;
		}

		int getCallbackID() const {
			return m_callbackID;
		}

		int getAnimSpeed() const {
			return m_animSpeed;
		}

		double getAngle() const {
			return m_angle;
		}

		Collider getCollider() const {
			return m_collider;
		}

	private:
		int m_x;
		int m_y;

		int m_width;
		int m_height;

		int m_numFrames;

		std::string m_textureID;

		int m_callbackID;
		int m_animSpeed;

		double m_angle;
		
		Collider m_collider;
	};
}
#endif
