#include "Door.h"
#include "Factory.h"

//-----------------------------------------------------------------------------
bool Door::m_registerit = Factory<StaticObject>::registerit("D",
	[](float height, float width, b2World* world) -> std::shared_ptr<StaticObject>
	{ return std::make_shared<Door>(height, width, world); });

//-----------------------------------------------------------------------------
Door::Door(float height, float width, b2World* world) :
	StaticObject(ResourcesAnimation::instance().animationData(ResourcesAnimation::Door),
		Direction::Stay, world, ResourcesAnimation::typeAnimationTexture::a_general, height, width)
{
	m_dir = Direction::Stay;
}
//-----------------------------------------------------------------------------
void Door::setIsOpenAnimation()
{
	m_limitedTimeOperation = m_limitedTimeOperation.Zero;
	m_dir = Direction::Up;
	m_animation.direction(Direction::Up);

}
