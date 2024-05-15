#pragma once
#include "ResourcesImages.h"
#include "ResourcesSounds.h"

class MainMenu
{
public:
	enum buttonType
	{
		e_play,
		e_exit,
		e_information,
		e_nothing

	};

	MainMenu();
	void run();
	void draw();
	MainMenu::buttonType clickOnMenu(sf::Vector2f click);
	void resizeButton(sf::Vector2f buttonLocation);
	bool checkIfClick(sf::Vector2f clickLocation, sf::Sprite sprite);

private:
	int m_winWidth;
	int m_winHeight;
	bool m_isExit = true;
	bool m_isPlay = true;
	bool m_isInformation = true;

	sf::Vector2f m_locationMouse;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Sprite m_exit;
	sf::Sprite m_play;
	sf::Sprite m_information;
	sf::Sprite m_informationScreen;
	sf::RenderWindow m_window;
};