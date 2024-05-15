#include "Springboard.h"
#include "Factory.h"

//-----------------------------------------------------------------------------
bool Springboard::m_registerit = Factory<StaticObject>::registerit("m",
	[](float height, float width, b2World* world) -> std::shared_ptr<StaticObject>
	{ return std::make_shared<Springboard>(height, width, world); });

//-----------------------------------------------------------------------------
Springboard::Springboard(float height, float width, b2World* world) : 
StaticObject(ResourcesAnimation::instance().animationData(ResourcesAnimation::Springboard),
	Direction::Stay, world, ResourcesAnimation::typeAnimationTexture::a_general, height, width)
{
	m_dir = Direction::Stay;
	b2PolygonShape groundBox;
	m_animation.setAnimationSpeed(0.05f);
}
//-----------------------------------------------------------------------------
void Springboard::setIsJump()
{
	m_limitedTimeOperation = m_limitedTimeOperation.Zero;
	m_dir = Direction::Up;
	m_animation.direction(Direction::Up);
}
