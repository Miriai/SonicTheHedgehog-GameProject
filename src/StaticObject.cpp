#include "StaticObject.h"

StaticObject::StaticObject(const AnimationData& data, Direction dir, b2World* world, 
	int typeTaxture, float height, float width)
	:m_animation(data, dir, m_sprite, typeTaxture)
{
	auto radius = (m_sprite.getGlobalBounds().width + m_sprite.getGlobalBounds().height) * SFML_SCALE * 0.3f;

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2CircleShape circle;

	circle.m_p.Set(0, 0);
	circle.m_radius = radius;
	bodyDef.type = b2_staticBody;
	m_body = world->CreateBody(&bodyDef);
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 3.f;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetFixedRotation(true);

	b2Vec2 startPos(width / BOX2D_SCALE, (height + 20.f) / BOX2D_SCALE); // delete the +20 
	m_body->SetTransform(startPos, 0);

	m_body->SetUserData(this);
}
//-----------------------------------------------------------------------------
void StaticObject::update(sf::Time delta)
{
	m_elapsed += delta;
	m_limitedTimeOperation += delta;

	if (m_limitedTimeOperation.asSeconds() > 0.2)
	{
		m_dir = Direction::Stay;
		m_animation.direction(Direction::Stay);
	}
	m_animation.update(delta);
}
//-----------------------------------------------------------------------------
void StaticObject::syncBoxAndSpriteLoc()
{
	b2Vec2 position = m_body->GetPosition();

	position *= BOX2D_SCALE;

	m_sprite.setPosition(position.x, position.y - 20);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f, m_sprite.getTextureRect().height / 2.f);
}