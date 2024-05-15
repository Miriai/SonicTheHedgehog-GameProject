#include "Wall.h"
#include "Enemy.h"
#include "SonicPlayer.h"
#include "Factory.h"


bool Wall::m_registerit = Factory<NonAnimationObject>::registerit("#",
	[](float height, float width, b2World* world, char type) -> std::shared_ptr<NonAnimationObject>
	{ return std::make_shared<Wall>(height, width, world, type); });


//-----------------------------------------------------------------------------
Wall::Wall(float height, float width , b2World* world, char type) 
{
	auto realType = ResourcesImages::imageType();

	switch (type)
	{
	case '(':
		realType = ResourcesImages::imageType::WallLeftChar;
		break;
	case '#':
		realType = ResourcesImages::imageType::WallMiddleChar;
		break;
	case ')':
		realType = ResourcesImages::imageType::WallRighteChar;
		break;
	case '<':
		realType = ResourcesImages::imageType::IslandLeftChar;
		break;
	case '=':
		realType = ResourcesImages::imageType::IslandMiddleChar;
		break;
	case '>':
		realType = ResourcesImages::imageType::IslandRighteChar;
		break;	
	case 'W':
		realType = ResourcesImages::imageType::WallClear;
		break;
	case 'A':
		realType = ResourcesImages::imageType::Water1;
		break;
	case 'S':
		realType = ResourcesImages::imageType::Water2;
		break;
	default:
		realType = ResourcesImages::imageType::WallMiddleChar;
		break;
	}

	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(realType));
	m_sprite.setPosition(width, height);

	b2PolygonShape groundBox;
	b2BodyDef bodyDef;

	bodyDef.position.Set((width/ BOX2D_SCALE), ((height)/BOX2D_SCALE));
	m_body = world->CreateBody(&bodyDef);
	groundBox.SetAsBox(m_sprite.getGlobalBounds().width * 0.005f, m_sprite.getGlobalBounds().height * 0.005f);
	m_body->CreateFixture(&groundBox, 0.0f);

	m_body->SetUserData(this);

}
//-----------------------------------------------------------------------