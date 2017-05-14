#pragma once
#include "math.h"
class vector2D
{
public:
	vector2D(){};
	vector2D(float x, float y) : m_x(x), m_y(y){}

	float getX(){ return m_x; }
	float getY(){ return m_y; }

	void setX(float x){ m_x = x; }
	void setY(float y){ m_y = y; }

	float lenght() { return sqrt(m_x*m_x + m_y*m_y); }

	vector2D operator+(const vector2D& v2) const
	{
		return vector2D(m_x + v2.m_x, m_y + v2.m_y);
	}

	friend vector2D& operator+=(vector2D& v1, const vector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;
		return v1;
	}

	vector2D operator*(float scalar)
	{
		return vector2D(m_x * scalar, m_y * scalar);
	}

	vector2D& operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;

		return *this;
	}

	vector2D operator-(const vector2D& v2)
	{
		return vector2D(m_x - v2.m_x, m_y - v2.m_y);
	}

	friend vector2D& operator-=(vector2D& v1, const vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;

		return v1;
	}

	vector2D operator/(float scalar)
	{
		return vector2D(m_x / scalar, m_y / scalar);
	}

	vector2D&  operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;

		return *this;
	}

	void normalize()
	{
		float l = lenght();
		if (l > 0)
		{
			(*this) /= l;
		}
	}

	~vector2D(){}

private:

	float m_x;
	float m_y;
};

