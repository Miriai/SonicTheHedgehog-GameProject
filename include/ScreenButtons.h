#pragma once
#include "ResourcesImages.h"
#include "ResourcesSounds.h"

class ScreenButtons
{
public:
	enum class typeButton
	{
		b_informationButton,
		b_pauseButton,
		b_continueButton,
		b_soundOnButton,
		b_soundOffButton,
		b_informationScreen,
		b_nothing
	};

	ScreenButtons();
	void draw(sf::RenderWindow& window);
	void setLocationButtons(sf::RenderWindow& window, sf::Vector2f viewCenter);
	ScreenButtons::typeButton clickOnButtons(sf::Vector2f click);
	bool checkIfClick(sf::Vector2f clickLocation, sf::Sprite button);

private:

	bool m_isInformation = false;
	std::map <typeButton, sf::Sprite> m_mapButtons;
};