#include "EnemyFish.h"
#include "Factory.h"

bool EnemyFish::m_registerit = Factory<MovingObject>::registerit("$", 
	[](float height, float width, b2World* world) -> std::shared_ptr<MovingObject>
	{ return std::make_shared<EnemyFish>(height, width, world); });
//-----------------------------------------------------------------------------
EnemyFish::EnemyFish(float height, float width, b2World* world) :
	Enemy(ResourcesAnimation::instance().animationData(ResourcesAnimation::Fish),
		Direction::Up, world, height , width)
{
	m_moveType = MoveType::m_UpDown;
}
