#include "MovingObject.h"

MovingObject::MovingObject(const AnimationData& data, Direction dir, b2World* world,
	int typeTaxture, float height, float width)
	:m_animation(data, dir, m_sprite, typeTaxture)/*, m_moveType(MoveType::None)*/
{}
//-----------------------------------------------------------------------------
void MovingObject::setAnimationDirection(Direction dir)
{
	if (m_dir != dir && dir == Direction::Left)
	{
		m_sprite.setScale(1, 1);
	}
	if (m_dir != dir && dir == Direction::Right)
	{
		m_sprite.setScale(-1, 1);
	}

	m_dir = dir;
	m_animation.direction(dir);
	m_animation.setAnimationSpeed(0.3f);

}
//-----------------------------------------------------------------------------
void MovingObject::update(sf::Time delta)
{
	move(delta);
	m_animation.update(delta);
}
//-----------------------------------------------------------------------------
std::unique_ptr<Move> MovingObject::setMove()
{
	m_isFirst = false;

	switch (m_moveType)
	{
	case MoveType::m_LeftRight:
		return std::make_unique<MoveLeftRight>(m_body, &m_sprite, &m_animation);
	case MoveType::m_UpDown:
		return std::make_unique<MoveUpDown>(m_body, &m_sprite, &m_animation);
	}
	return nullptr;
}
