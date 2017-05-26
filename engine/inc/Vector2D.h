#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <cmath>
#include <iostream>	

#define EPS 1e-6

namespace engine{

	class Vector2D{
	public:
		Vector2D(float x, float y) : m_x(x), m_y(y) {}
		Vector2D() : m_x(0), m_y(0) {}

		float getX() { return m_x; }
		float getY() { return m_y; }

		void setX(float x) { m_x = x; }
		void setY(float y) { m_y = y; }

		float length(){	return sqrt(m_x * m_x + m_y * m_y); }

		Vector2D operator+(const Vector2D& v2) const{
			return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
		}
		
		Vector2D& operator+=(const Vector2D& v2){
			m_x += v2.m_x;
			m_y += v2.m_y;

			return *this;
		}

		Vector2D operator*(const float scalar){ 
			return Vector2D(m_x * scalar, m_y * scalar); 
		}

		Vector2D& operator*=(const float scalar){
			m_x *= scalar;
			m_y *= scalar;

			return *this;
		}

		Vector2D operator-(const Vector2D& v2) const{
			return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
		}

		Vector2D& operator-=(const Vector2D& v2){
			m_x -= v2.m_x;
			m_y -= v2.m_y;

			return *this;
		}

		Vector2D operator/(const float scalar){
			return Vector2D(m_x / scalar, m_y / scalar);
		}

		Vector2D& operator /=(const float scalar){
			m_x /= scalar;
			m_y /= scalar;

			return *this;
		}

		Vector2D operator =(Vector2D* other){
			setX(other->getX());
			setY(other->getY());

			return *this;
		}

		Vector2D operator =(Vector2D other){
			setX(other.getX());
			setY(other.getY());

			return *this;
		}

		bool operator ==(Vector2D other){
			if(fabs(getX() - other.getX()) < EPS and fabs(getY() - other.getY()) < EPS){
				return true;
			}

			return false;
		}

		Vector2D norm(){
			float l = length();
			if(l > 0){
				return (*this) / l;
			}

			return *this;
		}

		double dot(Vector2D a){
			return m_x * a.getX() + m_y * a.getY();
		}

		static double angle(Vector2D target, Vector2D other){
			double angle = target.dot(other);
			angle /= target.length() * other.length();
			angle = acos(angle);

			angle = angle * 180.0 / acos(-1);

			if(target.getX() > 0){
				angle = 180 - angle;
			} else {
				angle = angle + 180;
			}

			return angle;
		}

	private:
		float m_x;
		float m_y;
	};

}
#endif
