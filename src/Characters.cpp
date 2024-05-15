#include "Characters.h"

Characters::Characters(const AnimationData& data, Direction dir, b2World* world,
	int typeTaxture, float height, float width)
: MovingObject(data, dir, world, typeTaxture, height, width)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2CircleShape circle;

	auto radius = (m_sprite.getGlobalBounds().width + m_sprite.getGlobalBounds().height) * SFML_SCALE * 0.5f;

	circle.m_p.Set(0, 0);
	circle.m_radius = radius;
	bodyDef.type = b2_dynamicBody;
	m_body = world->CreateBody(&bodyDef);
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetFixedRotation(true);

	b2Vec2 startPos(width / BOX2D_SCALE, height / BOX2D_SCALE);
	m_body->SetTransform(startPos, 0);

	m_body->SetUserData(this);
}
