#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector2D.h"


namespace engine{
	class Collider{
	public:
		Collider(int p_width, int p_height) : m_width(p_width), m_height(p_height) {

		}

		Collider() : m_width(0), m_height(0) {

		}

		int getWidth(){
			return m_width;
		}

		int getHeight(){
			return m_height;
		}

		void setWidth(int value){
			m_width = value;
		}

		void setHeight(int value){
			m_height = value;
		}
	private:
		int m_width;
		int m_height;
	};
}
#endif
