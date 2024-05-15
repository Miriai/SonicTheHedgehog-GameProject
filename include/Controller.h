#pragma once
#include <thread>
#include <experimental/vector>

#include "MainMenu.h"
#include "Information.h"
#include "ScreenButtons.h"
#include "MyListener.h"
#include "Board.h"
#include "Constant.h"

class Controller
{
public:

	Controller();
	void run();
	
private:

	void scanObjectsIconToMap();
	void setWindow();
	void draw();
	void drawObjects();
	void gameOver();
	void nextLevel();
	void handleEvents();
	void updateGameObjects();
	void updateScoreAndInformation();
	void resetData();
	void ScanObjectLevel();
	int setTimeToPrint();
	int getSonicIndex()const;
	void clearTrashObjects();
	void setBackGround();
	void  clicButton(ScreenButtons::typeButton task);
	void setDataLocationScreen();


	int m_sonicLive;
	int m_level;
	int m_score;
	int m_currCoinPlayer;
	int m_gameOver = false;
	sf::Clock m_deltaClock,
		m_levelClock;

	SonicPlayer *m_sonicPtr;
	sf::RenderWindow m_window;
	std::vector<std::shared_ptr<MovingObject>> m_movables;
	Board m_board;
	Information m_information;
	sf::Sprite m_backGround;
	b2World m_world;
	MyListener m_listener;
	sf::Keyboard::Key m_dirPress;
	ScreenButtons m_buttons;
};



