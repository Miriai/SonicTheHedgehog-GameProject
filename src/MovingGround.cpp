#include "MovingGround.h"
#include "Factory.h"

bool MovingGround::m_registerit = Factory<MovingObject>::registerit("~", [](float height, float width, b2World* world) -> std::shared_ptr<MovingObject>
	{ return std::make_shared<MovingGround>(height, width, world); });

MovingGround::MovingGround(float height, float width, b2World* world)
	:MovingObject(ResourcesAnimation::instance().animationData(ResourcesAnimation::MovingGround), 
		Direction::Right, world, ResourcesAnimation::typeAnimationTexture::a_general, height, width)
{
	m_moveType = MoveType::m_LeftRight;
	auto radius = (m_sprite.getGlobalBounds().width + m_sprite.getGlobalBounds().height) * SFML_SCALE;

	auto x = m_sprite.getGlobalBounds().width * SFML_SCALE * 2.f;
	auto y = m_sprite.getGlobalBounds().height * SFML_SCALE * 2.f;
	//if type of sonic.

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape box;

	box.SetAsBox(x, y);
	bodyDef.type = b2_kinematicBody;
	m_body = world->CreateBody(&bodyDef);
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 3.f;
	m_body->CreateFixture(&fixtureDef);
	//m_body->SetFixedRotation(true);

	b2Vec2 startPos(width / BOX2D_SCALE, height / BOX2D_SCALE);
	m_body->SetTransform(startPos, 0);

	m_body->SetUserData(this);
}

void MovingGround::move(sf::Time deltaTime)
{
	m_elapsed += deltaTime;

	if (m_isFirst)
		m_move = setMove();

	m_move->move(deltaTime);
}

