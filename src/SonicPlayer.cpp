#include "SonicPlayer.h"
#include "Wall.h"
#include "Enemy.h"

//forward declaration
template <class T>
class Factory;

bool SonicPlayer::m_registerit = Factory<MovingObject>::registerit("@",
	[](float height, float width, b2World* world) -> std::shared_ptr<MovingObject>
	{ return std::make_shared<SonicPlayer>(height, width, world); });

//-----------------------------------------------------------------------------
SonicPlayer::SonicPlayer(float height, float width, b2World* world)
	: m_live(BEGIN_LIFE), m_totalTime(RESET), m_rings(RESET), m_timeProtected(RESET),
	Characters(ResourcesAnimation::instance().animationData(ResourcesAnimation::Sonic), Direction::Right, world,
		ResourcesAnimation::typeAnimationTexture::a_sonic, height, width)
{
	auto radius = (m_sprite.getGlobalBounds().width + m_sprite.getGlobalBounds().height) * SFML_SCALE * OBJECT_SIZE;
	m_shieldCircle.setRadius(radius);
	m_shieldCircle.setFillColor(sf::Color{ 222,222,222, 127 });
	m_shieldCircle.setOutlineThickness(1.f);
}
//-----------------------------------------------------------------------------
void SonicPlayer::increaseRings()
{
	++m_rings;
}
//-----------------------------------------------------------------
void SonicPlayer::increaseDimond()
{
	m_rings += DIMOND_BONUS;
}
//-----------------------------------------------------------------------------
int SonicPlayer::getRings()const
{
	return m_rings;
}
//-----------------------------------------------------------------------------
void SonicPlayer::setSubLive()
{
	if (m_elapsedInjured.asSeconds() > 0.1f)
	{
		m_elapsedInjured = m_elapsedInjured.Zero;
		--m_live;
	}
}
//-----------------------------------------------------------------------------
int SonicPlayer::getLive() const
{
	return m_live;
}
//-----------------------------------------------------------------------------
void SonicPlayer::setLive(int live)
{
	m_live = live;
}
//-----------------------------------------------------------------------------
//if the player collision with enemy or thorn
void SonicPlayer::impulseBack()
{
	if (m_dir == Direction::Left)
		m_body->SetLinearVelocity({ 6 ,-3 });

	else
		m_body->SetLinearVelocity({ -6 ,-3 });
}
//-----------------------------------------------------------------------------
bool SonicPlayer::getIsProtected() const
{
	return m_protected;
}
//-----------------------------------------------------------------------------
void SonicPlayer::setIsProtected(bool isProtected, float time)
{
	m_elapsed = m_elapsed.Zero;
	m_protected = isProtected;
	m_timeProtected = time;
}
//-----------------------------------------------------------------------------
void SonicPlayer::updateProtected()
{
	if (m_dir == Direction::Down)
	{
		m_protected = true;
	}

	if (m_elapsed.asSeconds() > m_timeProtected)
	{
		m_protected = false;
	}
}
//-----------------------------------------------------------------------------
void SonicPlayer::setDirection()
{
	m_elapsed = m_elapsed.Zero;
	m_dir = Direction::Stay;
}
//-----------------------------------------------------------------------------
void SonicPlayer::impulsSpringJump()
{
	m_body->SetLinearVelocity({ m_body->GetLinearVelocity().x, -10.f });
	setPlayerAnimation(Direction::Jump, 0.04f);
}
//-----------------------------------------------------------------------------
bool SonicPlayer::getIsFinishLevel() const
{
	return m_isFinishLevel;
}
//-----------------------------------------------------------------------------
void SonicPlayer::setIsFinishLevel(bool finish)
{
	m_isFinishLevel = finish;
}
//-----------------------------------------------------------------------------
void SonicPlayer::move(sf::Time deltaTime)
{
	m_elapsed += deltaTime;
	m_limitedTimeOperation += deltaTime;
	m_elapsedJump += deltaTime;
	m_elapsedInjured += deltaTime;

	auto speed = 3.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_elapsedJump.asSeconds() > 1.f)
	{
		m_body->SetLinearVelocity({ m_body->GetLinearVelocity().x, -8.f });
		m_elapsedJump = m_elapsedJump.Zero;
		setPlayerAnimation(Direction::Up, 0.03f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		m_body->SetLinearVelocity({ -speed, m_body->GetLinearVelocity().y });
		if (m_body->GetLinearVelocity().y == 0 && m_boostSpeed == 0.3f)
			setPlayerAnimation(Direction::Left, 0.1f);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		m_body->SetLinearVelocity({ speed, m_body->GetLinearVelocity().y });

		if (m_body->GetLinearVelocity().y == 0 && m_boostSpeed == 0.3f)
			setPlayerAnimation(Direction::Right, 0.1f);
	}

	if (m_body->GetLinearVelocity().y < 0.1f && m_body->GetLinearVelocity().x != 0)
		moveDown();

	if (abs(m_body->GetLinearVelocity().x) <= 1 && m_body->GetLinearVelocity().y == 0)
		setPlayerAnimation(Direction::Stay, 0.3f);
}
//-----------------------------------------------------------------------------
void SonicPlayer::moveDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (m_limitedTimeOperation.asSeconds() > 0.2f && m_boostSpeed <= 10.f)
		{
			m_limitedTimeOperation = m_limitedTimeOperation.Zero;
			++m_boostSpeed;
		}

		if (m_leftOrRight == Direction::Left)
			m_body->SetLinearVelocity({ -m_boostSpeed, m_body->GetLinearVelocity().y });
		else if (m_leftOrRight == Direction::Right)
			m_body->SetLinearVelocity({ m_boostSpeed, m_body->GetLinearVelocity().y });

		if (m_boostSpeed > 5.f)
		{
			ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::BoostRun);
			setPlayerAnimation(Direction::Roll, 0.04f);
			setIsProtected(true, 0.2f);
		}
		else
			setPlayerAnimation(Direction::Down, 0.04f);
	}
	else
		m_boostSpeed = 0.3f;


}
//-----------------------------------------------------------------------------
void SonicPlayer::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);

	if (m_protected)
	{
		b2Vec2 position = m_body->GetWorldCenter();
		position *= BOX2D_SCALE;
		m_shieldCircle.setPosition(position.x + 35, position.y + 35);
		m_shieldCircle.setOrigin(m_sprite.getTextureRect().width / 2.f, m_sprite.getTextureRect().height / 2.f);

		window.draw(m_shieldCircle);
	}
}
//-----------------------------------------------------------------------------
void SonicPlayer::setPlayerAnimation(Direction dir, float speed)
{
	if (dir == Direction::Left || dir == Direction::Right)
		m_leftOrRight = dir;

	if (dir == Direction::Up)
		ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::Jump);

	setAnimationDirection(dir);
	m_animation.setAnimationSpeed(speed);
	m_dir = dir;

}

