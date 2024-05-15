#pragma once
#include "GameObject.h"
#include "Animation.h"

class StaticObject : public GameObject
{
public:
	StaticObject(const AnimationData& data, Direction dir, b2World* world, int typeTaxture, float height, float width);
	void update(sf::Time delta)override;
	virtual void syncBoxAndSpriteLoc()override;

protected:

	Animation m_animation;
	Direction m_dir = Direction::Stay;
	sf::Time m_elapsed = {};
	sf::Time m_limitedTimeOperation = {};
private:

};