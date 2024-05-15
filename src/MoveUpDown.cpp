#include "MoveUpDown.h"

MoveUpDown::MoveUpDown(b2Body* body, sf::Sprite* sprite, Animation* animation):
	Move(body, sprite, animation)
{
	m_moveDirection = toVector(Direction::Up);
}
//-----------------------------------------------------------------------------
void MoveUpDown::move(sf::Time deltaTime)
{
	m_elapsed += deltaTime;

	if (m_elapsed.asSeconds() > 2)
	{
		(m_moveDirection == toVector(Direction::Up)) ? m_moveDirection = toVector(Direction::Stay) :
			m_moveDirection = toVector(Direction::Up);

		m_elapsed = m_elapsed.Zero;
	}
	if (m_moveDirection == toVector(Direction::Up))
	{
		m_body->SetLinearVelocity({ 0 , -1});
		m_animation->direction(Direction::Up);

	}
	else if (m_moveDirection == toVector(Direction::Stay))
		m_animation->direction(Direction::Stay);
	
}
