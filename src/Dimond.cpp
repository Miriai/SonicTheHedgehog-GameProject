#include "Dimond.h"
#include "Factory.h"

//-----------------------------------------------------------------------------
bool Dimond::m_registerit = Factory<StaticObject>::registerit("^",
	[](float height, float width, b2World* world) -> std::shared_ptr<StaticObject>
	{ return std::make_shared<Dimond>(height, width, world); });

//-----------------------------------------------------------------------------
Dimond::Dimond(float height, float width, b2World* world) :
	StaticObject(ResourcesAnimation::instance().animationData(ResourcesAnimation::Dimond),
		Direction::Stay, world, ResourcesAnimation::typeAnimationTexture::a_general, height, width)
{
	m_dir = Direction::Stay;
}
