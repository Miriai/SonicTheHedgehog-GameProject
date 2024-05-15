#include "ScreenButtons.h"

#include <iostream> //--> delete! 

ScreenButtons::ScreenButtons()
{
	m_mapButtons[typeButton::b_informationButton].setTexture(ResourcesImages::getInstance()
		.getTexture(ResourcesImages::imageType::InformationButton));
	m_mapButtons[typeButton::b_soundOnButton].setTexture(ResourcesImages::getInstance()
		.getTexture(ResourcesImages::imageType::SoundOnButton));
	m_mapButtons[typeButton::b_soundOffButton].setTexture(ResourcesImages::getInstance()
		.getTexture(ResourcesImages::imageType::SoundOffButton));
	m_mapButtons[typeButton::b_pauseButton].setTexture(ResourcesImages::getInstance()
		.getTexture(ResourcesImages::imageType::PauseButton));
	m_mapButtons[typeButton::b_informationScreen].setTexture(ResourcesImages::getInstance()
		.getTexture(ResourcesImages::imageType::InformationScreen));
}
//-----------------------------------------------------------------------------
void ScreenButtons::draw(sf::RenderWindow& window)
{
	for (auto it = m_mapButtons.begin(); it != m_mapButtons.end(); ++it)
	{
		if(it->first != typeButton::b_informationScreen)
			window.draw(it->second);
		else if (m_isInformation == true)
			window.draw(it->second);
	}
}
//-----------------------------------------------------------------------------
void ScreenButtons::setLocationButtons(sf::RenderWindow& window, sf::Vector2f viewCenter)
{
	auto counter = OBJECT_SIZE * 2;
	viewCenter.y += OBJECT_SIZE;

	for (auto it = m_mapButtons.begin(); it != m_mapButtons.end(); ++it)
	{
		it->second.setPosition(viewCenter.x - (window.getSize().x / 2) + counter,
			viewCenter.y - (window.getSize().y / 2));
		counter += OBJECT_SIZE;
	}
}
//-----------------------------------------------------------------------------
ScreenButtons::typeButton ScreenButtons::clickOnButtons(sf::Vector2f click)
{
	if (checkIfClick(click, m_mapButtons[typeButton::b_informationButton])) {
		m_isInformation = !m_isInformation;
		return typeButton::b_informationButton;
	}
	else if (checkIfClick(click, m_mapButtons[typeButton::b_soundOnButton]))
		return typeButton::b_soundOnButton; 
	else if (checkIfClick(click, m_mapButtons[typeButton::b_soundOffButton]))
		return typeButton::b_soundOffButton;
	else if (checkIfClick(click, m_mapButtons[typeButton::b_pauseButton]))
		return typeButton::b_pauseButton;
	else if (checkIfClick(click, m_mapButtons[typeButton::b_continueButton]))
		return typeButton::b_continueButton;

		return typeButton::b_nothing;
}
//-----------------------------------------------------------------------------
bool ScreenButtons::checkIfClick(sf::Vector2f clickLocation, sf::Sprite button)
{
	if (clickLocation.x > button.getPosition().x &&
		clickLocation.x < button.getPosition().x + button.getGlobalBounds().width)
		if (clickLocation.y > button.getPosition().y &&
			clickLocation.y < button.getPosition().y + button.getGlobalBounds().height) {

			ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::OnButton);

			return true;
		}

	return false;
}
