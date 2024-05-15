#include "EnemyCrab.h"
#include "Factory.h"

bool EnemyCrab::m_registerit = Factory<MovingObject>::registerit("%", 
	[](float height, float width, b2World* world) -> std::shared_ptr<MovingObject>
	{ return std::make_shared<EnemyCrab>(height, width, world); });

//-----------------------------------------------------------------------------
EnemyCrab::EnemyCrab(float height, float width, b2World* world):
	Enemy(ResourcesAnimation::instance().animationData(ResourcesAnimation::Crab), 
		Direction::Right, world ,height, width)
{
	m_moveType = MoveType::m_LeftRight;
}
