#include "Shield.h"
#include "Factory.h"

//-----------------------------------------------------------------------------
bool Shield::m_registerit = Factory<StaticObject>::registerit("+", 
	[](float height, float width, b2World* world) -> std::shared_ptr<StaticObject>
	{ return std::make_shared<Shield>(height, width, world); });

//-----------------------------------------------------------------------------
Shield::Shield(float height, float width, b2World* world) :
	StaticObject(ResourcesAnimation::instance().animationData(ResourcesAnimation::Shield),
		Direction::Stay, world, ResourcesAnimation::typeAnimationTexture::a_general, height, width)
{
	m_dir = Direction::Stay;
}
