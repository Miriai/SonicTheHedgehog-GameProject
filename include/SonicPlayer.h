#pragma once
#include "Board.h"
#include "Characters.h"
#include "Constant.h"

//Forward declaration
template <class T>
class Factory;

class SonicPlayer : public Characters
{
public:
	SonicPlayer(float height, float width, b2World* world);
	void increaseRings();
	void increaseDimond();
	int getRings()const;
	void setSubLive();
	void impulseBack();
	bool getIsProtected() const;
	void setIsProtected(bool isProtected, float time);
	void updateProtected();
	void setDirection();
	void impulsSpringJump();
	bool getIsFinishLevel()const;
	void setIsFinishLevel(bool finish);
	int getLive() const;
	void setLive(int live);
	void move(sf::Time deltaTime)override;
	void moveDown();
	void draw(sf::RenderWindow& window)override;
	void setPlayerAnimation(Direction dir, float speed);

private:
	int m_rings, m_live;
	bool m_isFirst = true;
	bool m_isFinishLevel = false;
	
	float m_totalTime;
	static bool m_registerit;
	Direction m_leftOrRight = Direction::Left;
	bool m_protected = false;
	float m_timeProtected;
	float m_boostSpeed = 3.f;
	sf::CircleShape m_shieldCircle;
	sf::Time m_elapsedJump = {};
	sf::Time m_elapsedInjured = {};

};
//-----------------------------------------------------------------------------
