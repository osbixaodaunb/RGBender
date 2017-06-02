#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector2D.h"


namespace engine{
	class Collider{
	public:
		Collider(Vector2D p_center, int p_width, int p_height) : m_center(p_center), m_width(p_width), m_height(p_height) {

		}

		Collider() : m_center(0, 0), m_width(0), m_height(0) {

		}

		Vector2D getCenter(){
			return m_center;
		}

		Vector2D getMin(){
			return Vector2D(m_center.getX() - m_width/2, m_center.getY() - m_height/2);
		}

		Vector2D getMax(){
			return Vector2D(m_center.getX() + m_width/2, m_center.getY() + m_height/2);
		}

		int getWidth(){
			return m_width;
		}

		int getHeight(){
			return m_height;
		}
	private:
		Vector2D m_center;
		int m_width;
		int m_height;
	};
}
#endif
