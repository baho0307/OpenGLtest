#include "square.hpp"
#include<cstdlib>

Square::Square(float x, float y, float length)
{
	m_Pos = glm::vec3(x, y, 0.0f);
	m_Color.r = (10 + std::rand() % 15) / 25.0;
	m_Color.g = (10 + std::rand() % 15) / 25.0;
	m_Length = length;
	m_Direction = DIR_RIGHT;

}

glm::vec3 Square::getPosition()
{
	return m_Pos;
}

glm::vec4 Square::getColor()
{
	return m_Color;
}

void Square::move(float amount)
{
	switch (m_Direction)
	{
		case DIR_LEFT:
			m_Pos += glm::vec3(-m_Length * amount, 0.0f, 0.0f);
		break;
		case DIR_RIGHT:
			m_Pos += glm::vec3(m_Length * amount, 0.0f, 0.0f);
		break;
		case DIR_UP:
			m_Pos += glm::vec3(0.0f, m_Length * amount, 0.0f);
		break;
		case DIR_DOWN:
			m_Pos += glm::vec3(0.0f , -m_Length * amount, 0.0f);
		break;
	}
}

void Square::setDirection(Square::DIRECTION dir)
{
	m_Direction = dir;
}

Square::DIRECTION Square::getDirection()
{
	return m_Direction;
}