#include "Ring.h"
#include "Factory.h"

//-----------------------------------------------------------------------------
bool Ring::m_registerit = Factory<StaticObject>::registerit("*",
	[](float height, float width, b2World* world) -> std::shared_ptr<StaticObject>
	{ return std::make_shared<Ring>(height, width, world); });

//-----------------------------------------------------------------------------
Ring::Ring(float height, float width ,b2World* world):
	StaticObject(ResourcesAnimation::instance().animationData(ResourcesAnimation::Ring),
		Direction::Stay, world, ResourcesAnimation::typeAnimationTexture::a_general, height, width)
{
	m_dir = Direction::Stay;
}
