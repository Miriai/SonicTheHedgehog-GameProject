#pragma once
#include "GameObject.h"

#include "MoveLeftRight.h"
#include "MoveUpDown.h"

//Forward declaration
class Wall;

class MovingObject : public GameObject
{
public:

	MovingObject(const AnimationData& data, Direction dir, b2World* world, int typeTaxture, float height, float width);

	//to delete enemy
	void setAnimationDirection(Direction dir);
	void update(sf::Time delta)override;
	virtual void move(sf::Time deltaTime) = 0;
	std::unique_ptr<Move>setMove();
	

protected:

	MoveType m_moveType;
	bool m_isFirst = true;
	std::unique_ptr<Move> m_move;

	Animation m_animation;
	sf::Vector2f m_startLocation;
	Direction m_dir = Direction::Stay;

	sf::Time m_elapsed = {};
	sf::Time m_limitedTimeOperation = {};

private:
	
};
//-----------------------------------------------------------------------------

