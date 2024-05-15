#include "MoveLeftRight.h"
#include <iostream>
MoveLeftRight::MoveLeftRight(b2Body* body, sf::Sprite* sprite, Animation* animation):
	Move(body, sprite, animation)
{
	srand((unsigned int)time(NULL));

	( rand() % 2 == 1) ? m_moveDirection = toVector(Direction::Left) : toVector(Direction::Right);
}
//-----------------------------------------------------------------------------
void MoveLeftRight::move(sf::Time deltaTime)
{
	m_elapsed += deltaTime;
	if (m_elapsed.asSeconds() > 3)
	{
		auto dir = rand() % 3;

		switch (dir)
		{
		case 0:
			m_moveDirection = toVector(Direction::Left);
			break;
		case 1:
			m_moveDirection = toVector(Direction::Right);
			break;
		case 2:
			m_moveDirection = toVector(Direction::Stay);
			break;
		}

		m_elapsed = m_elapsed.Zero;
	}
	if (m_moveDirection == toVector(Direction::Left))
	{
		m_body->SetLinearVelocity({ -1 , m_body->GetLinearVelocity().y });
		m_animation->direction(Direction::Right);
		m_sprite->setScale(-1, 1);

	}
	else if (m_moveDirection == toVector(Direction::Right))
	{
		m_body->SetLinearVelocity({ 1 ,m_body->GetLinearVelocity().y });
		m_animation->direction(Direction::Right);
		m_sprite->setScale(1, 1);

	}
	else
		m_animation->direction(Direction::Stay);

}
