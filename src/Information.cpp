#include "Information.h"

//-----------------------------------------------------------------------------
Information::Information(int score, int live, int time, int level, float height, float width) :
	m_score(score), m_live(live), m_time(time), m_level(level), m_height(height), m_width(width)
{
	if (!m_font.loadFromFile("FontFile.ttf"))
		throw  std::runtime_error("Can't load font file...");


	setText(text[0], sf::Color::Yellow, "Score ", height, width);
	setText(text[1], sf::Color::Red, std::to_string(score), height, width);
	setText(text[2], sf::Color::Yellow, "Live ", height, width);
	setText(text[3], sf::Color::Red, std::to_string(live), height, width);
	setText(text[4], sf::Color::Yellow, "Level ", height, width);
	setText(text[5], sf::Color::Red, std::to_string(level), height, width);
	setText(text[6], sf::Color::Yellow, "Time ", height, width);
	setText(text[7], sf::Color::Red, std::to_string(time), height, width);
}

//-----------------------------------------------------------------------------
void Information::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUM_TEXT; i++)
		window.draw(text[i]);
}
//-----------------------------------------------------------------------------
void Information::setPosition(sf::Vector2u windowSize, sf::Vector2f viewCenter)
{
	auto counter = 400.f;

	viewCenter.y += OBJECT_SIZE;

	for (int i = 0; i < MAX_NUM_TEXT; i++)
	{
		text[i].setPosition(viewCenter.x - (windowSize.x / 2) + counter,
			viewCenter.y - (windowSize.y / 2));
		counter += 110;
	}
}
//-----------------------------------------------------------------------------
void Information::setInformation(int score, int live, int time, int level)
{
	text[1].setString(std::to_string(score));
	text[3].setString(std::to_string(live));
	text[5].setString(std::to_string(level));
	text[7].setString(std::to_string(time));
}
//-----------------------------------------------------------------------------
void Information::setText(sf::Text& text,const sf::Color& color, std::string str,
	float height, float width)
{
	text.setString(str);
	text.setPosition(width, height);
	text.setFont(m_font);
	text.setFillColor(color);
}
//-----------------------------------------------------------------------------
