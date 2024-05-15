#include "EnemyBat.h"
#include "Factory.h"

bool EnemyBat::m_registerit = Factory<MovingObject>::registerit("&", 
	[](float height, float width, b2World* world) -> std::shared_ptr<MovingObject>
	{ return std::make_shared<EnemyBat>(height, width, world); });

//-----------------------------------------------------------------------------
EnemyBat::EnemyBat(float height, float width, b2World* world) :
	Enemy(ResourcesAnimation::instance().animationData(ResourcesAnimation::Bat),
		Direction::Right, world, height, width)
{
	m_moveType = MoveType::m_LeftRight;
}
