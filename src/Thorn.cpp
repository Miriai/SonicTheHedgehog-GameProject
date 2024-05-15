#include "Thorn.h"
#include "Factory.h"


bool Thorn::m_registerit = Factory<NonAnimationObject>::registerit("Z", 
	[](float height, float width, b2World* world, char type) -> std::shared_ptr<NonAnimationObject>
	{ return std::make_shared<Thorn>(height, width, world, type); });


//-----------------------------------------------------------------------------
Thorn::Thorn(float height, float width, b2World* world, char type)
{

	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::Thorn));
	m_sprite.setPosition(width, height);

	b2PolygonShape groundBox;
	b2BodyDef bodyDef;

	bodyDef.position.Set((width / BOX2D_SCALE), ((height) / BOX2D_SCALE));
	m_body = world->CreateBody(&bodyDef);
	groundBox.SetAsBox(m_sprite.getGlobalBounds().width * 0.005f, m_sprite.getGlobalBounds().height * 0.005f);
	m_body->CreateFixture(&groundBox, 0.0f);

	m_body->SetUserData(this);

}
//-----------------------------------------------------------------------
