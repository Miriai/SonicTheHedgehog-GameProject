#pragma once
#include <box2d/box2d.h>

#include "ResourcesImages.h"
#include "ResourcesSounds.h"
#include "ResourcesAnimation.h"

class GameObject
{
public:

	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& window);
	virtual void syncBoxAndSpriteLoc();
	virtual void update(sf::Time delta) = 0;

	void setLocation(float height, float width);
	void setDisposed();
	bool isDisposed() const;
	b2Body* getBody();
	sf::Sprite getSprite();

protected:

	bool m_isDisposed = false;
	sf::Sprite m_sprite;
	b2Body* m_body;

private:
};
//-------------------------------------------------------------
