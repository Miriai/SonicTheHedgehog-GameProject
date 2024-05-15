#include "MainMenu.h"


MainMenu::MainMenu()
{
	m_informationScreen.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::InformationScreen));
	m_informationScreen.setPosition(115, 115);


	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::Open));

	m_winWidth = ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::Open).getSize().x;
	m_winHeight = ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::Open).getSize().y;

	m_play.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::PlayButton));
	m_play.setPosition(m_winWidth * 0.2f, m_winHeight * 0.7f);


	m_exit.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::ExitButton));
	m_exit.setPosition(m_winWidth * 0.5f, m_winHeight * 0.7f);

	m_information.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::InformationButton));
	m_information.scale(0.8f, 0.8f);
	m_information.setPosition(50.f, 50.f);
}
//-----------------------------------------------------------------------------
void MainMenu::run()
{

	m_window.close();
	m_window.create(sf::VideoMode(m_winWidth, m_winHeight), "Opening");


	while (m_window.isOpen())
	{
		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			m_locationMouse = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::MouseButtonReleased:
				auto clickLocation = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					switch (clickOnMenu(clickLocation))
					{
					case e_play:
						m_window.close();
						break;
					case e_exit:
						exit(EXIT_SUCCESS);
					}

					break;
				}
				break;
			}
		}
		draw();
	}
}
//-----------------------------------------------------------------------------
void MainMenu::draw()
{
	resizeButton(m_locationMouse);

	m_window.clear();
	m_window.draw(m_sprite);
	m_window.draw(m_exit);
	m_window.draw(m_play);
	m_window.draw(m_information);

	if (!m_isInformation)
		m_window.draw(m_informationScreen);

	m_window.display();
}

//-----------------------------------------------------------------------------
MainMenu::buttonType MainMenu::clickOnMenu(sf::Vector2f click)
{
	if(checkIfClick(click, m_exit))
		return buttonType::e_exit;

	else if (checkIfClick(click, m_play))
		return buttonType::e_play;

	else if (checkIfClick(click, m_information))
		return buttonType::e_information;

	return e_nothing;
}
//-----------------------------------------------------------------------------
bool MainMenu::checkIfClick(sf::Vector2f clickLocation, sf::Sprite button)
{
	if (clickLocation.x > button.getPosition().x &&
		clickLocation.x < button.getPosition().x + button.getGlobalBounds().width)
		if (clickLocation.y > button.getPosition().y &&
			clickLocation.y < button.getPosition().y + button.getGlobalBounds().height) {
			return true;
		}

	return false;
}
//-----------------------------------------------------------------------------
void MainMenu::resizeButton(sf::Vector2f buttonLocation)
{
	int click = clickOnMenu(buttonLocation);

	if (click == e_exit && m_isExit)
	{
		m_isExit = false;
		ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::OnButton);
		m_exit.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::ExitBigButton));
		m_exit.setPosition(m_winWidth * 0.5f, m_winHeight * 0.7f);
	}

	else if (click != e_exit && !m_isExit)
	{
		m_exit.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::ExitButton));
		m_exit.setPosition(m_winWidth * 0.5f, m_winHeight * 0.7f);
		m_isExit = true;
	}

	if (click == e_play && m_isPlay)
	{
		m_isPlay = false;
		ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::OnButton);
		m_play.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::PlayBigButton));
		m_play.setPosition(m_winWidth * 0.2f, m_winHeight * 0.7f);
	}
	else if (click != e_play && !m_isPlay)
	{
		m_play.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::PlayButton));
		m_play.setPosition(m_winWidth * 0.2f, m_winHeight * 0.7f);
		m_isPlay = true;
	}

	if (click == e_information && m_isInformation)
		m_isInformation = false;
	
	else if (click != e_information && !m_isInformation)
		m_isInformation = true;
	
}