#include "WoodBox.h"
#include "Factory.h"

bool WoodBox::m_registerit = Factory<NonAnimationObject>::registerit("?",
	[](float height, float width, b2World* world, char type) -> std::shared_ptr<NonAnimationObject>
	{ return std::make_shared<WoodBox>(height, width, world, type); });

//-----------
WoodBox::WoodBox(float height, float width, b2World* world, char type)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::WoodBox));
	m_sprite.setPosition(width, height);

	auto x = m_sprite.getGlobalBounds().width * 0.005f;
	auto y = m_sprite.getGlobalBounds().height * 0.005f;
	//if type of sonic.

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape box;

	box.SetAsBox(x, y);
	bodyDef.type = b2_dynamicBody;
	m_body = world->CreateBody(&bodyDef);
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 3.f;
	m_body->CreateFixture(&fixtureDef);

	b2MassData mass{ 5, m_body->GetLocalCenter(),m_body->GetInertia() };

	m_body->SetMassData(&mass);
	//m_body->SetFixedRotation(true);

	b2Vec2 startPos(width / BOX2D_SCALE, height / BOX2D_SCALE);
	m_body->SetTransform(startPos, 0);

	m_body->SetUserData(this);
}
