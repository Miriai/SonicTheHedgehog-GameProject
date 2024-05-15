#include "Controller.h"

const auto GRAVITY = b2Vec2({ 0.0f, 15.f });
const int32 VELOCITY_ITERATIONS = 6;
const int32 POSITION_ITERATIONS = 2;

//=============================================================================
Controller::Controller() :m_level(FIRST_LEVEL), m_currCoinPlayer(RESET),
m_score(RESET), m_information(RESET, RESET, RESET, RESET, RESET, RESET),
m_world(GRAVITY), m_sonicLive(BEGIN_LIFE)
{
	ResourcesSounds::getInstance().setLoopPlay(ResourcesSounds::soundType::Background1);
	ResourcesSounds::getInstance().setValume(10.f);
	MainMenu().run();

	m_board.setWorld(&m_world);
	m_board.scanMap();
	m_board.scanObjectsIconToMap();
	scanObjectsIconToMap();
	setWindow();
	m_deltaClock.restart();

	m_backGround.setTexture(ResourcesImages::getInstance().
		getTexture(ResourcesImages::imageType::BackGroundLevel1));

	m_world.SetContactListener(&m_listener);
	m_sonicPtr = &dynamic_cast<SonicPlayer&>(*m_movables[getSonicIndex()]);
}
//=============================================================================
void Controller::run()
{
	//main loop 
	while (m_window.isOpen())
	{
		handleEvents();						 //handle window events
		updateGameObjects();				
		updateScoreAndInformation();
		m_board.checkWhichObejectDelete();  //check if non animation object is isDisposed
		clearTrashObjects();				//check if object is isDisposed
		setDataLocationScreen();
		draw();
	}
}
//-----------------------------------------------------------------------------
void Controller::scanObjectsIconToMap()
{
	for (int height = 0; height < m_board.getHeight(); height++) {
		for (int width = 0; width < m_board.getWidth(); width++) {

			auto typeObject = std::string(1, m_board.getCharObject(height, width));
			auto object = Factory<MovingObject>::create(typeObject, height * OBJECT_SIZE, width * OBJECT_SIZE, &m_world);

			if (object)
				m_movables.push_back(std::move(object));
		}
	}
}
//-----------------------------------------------------------------------------
void Controller::setWindow()
{
	m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Sonic The Hedgehog");
}
//-----------------------------------------------------------------------------
void Controller::drawObjects()
{
	m_board.drawStaticObjects(m_window);

	for (auto& movable : m_movables)
		movable->draw(m_window);
}
//-----------------------------------------------------------------------------
void Controller::gameOver()
{
	sf::Sprite over;
	over.setTexture(ResourcesImages::getInstance().getTexture(ResourcesImages::imageType::GameOver));
	over.setOrigin(over.getTextureRect().width / 2.f, over.getTextureRect().height / 2.f);
	over.setPosition(m_window.getView().getCenter().x,
		m_window.getView().getCenter().y);
	ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::GameOver);

	m_window.clear();
	drawObjects();
	m_window.draw(over);
	m_window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	m_window.close();
	MainMenu().run();

	m_gameOver = true;

	resetData();
	ScanObjectLevel();
	setWindow();

	m_gameOver = false;
}
//-----------------------------------------------------------------------------
void Controller::nextLevel()
{
	m_level++;
	m_sonicPtr->setIsFinishLevel(false);
	m_score += BONUS_LEVEL * m_level;

	m_sonicPtr->setLive(BEGIN_LIFE);
	setWindow();
	resetData();
	ScanObjectLevel();
}
//-----------------------------------------------------------------------------
void Controller::draw()
{
	m_window.clear();
	m_window.setFramerateLimit(60);
	m_window.draw(m_backGround);
	drawObjects();
	m_information.draw(m_window);
	m_buttons.draw(m_window);
	m_window.display();
}
//-----------------------------------------------------------------------------
//keyboard events 
void Controller::handleEvents()
{
	for (auto event = sf::Event(); m_window.pollEvent(event);)
		switch (event.type)
		{

		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
				break;
			}
			break;

		case sf::Event::MouseButtonReleased:
			auto clickLocation = m_window.mapPixelToCoords({ event.mouseButton.x,
				event.mouseButton.y });

			switch (event.mouseButton.button)
			{
			case sf::Mouse::Button::Left:
				auto task = (m_buttons.clickOnButtons(clickLocation));
				clicButton(task);
			}
			break;
		}
}
//-----------------------------------------------------------------------------
//moving function && check if return wall && check isFall
void Controller::updateGameObjects()
{
	m_world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	const auto deltaTime = m_deltaClock.restart();

	for (auto& movable : m_movables)
	{
		movable->update(deltaTime);
		movable->syncBoxAndSpriteLoc();
	}

	m_sonicPtr->updateProtected(); //check if sonic need shield
	m_board.syncObjectToWorld();  //sync the box2d and sfml objects
	m_board.updateStaticAnimation(deltaTime); 
}
//-----------------------------------------------------------------------------
void Controller::updateScoreAndInformation()
{
	//if the player lose -> game over
	if (m_sonicPtr->getLive() <= 0)
		gameOver();
	//check if the player finish the level
	if (m_sonicPtr->getIsFinishLevel())
		nextLevel();

	//update the data information bar on the screen
	if (m_currCoinPlayer < m_sonicPtr->getRings())
	{
		m_score += (SCORE_PER_COIN * m_level) * (m_sonicPtr->getRings() - m_currCoinPlayer);
		m_currCoinPlayer = m_sonicPtr->getRings();
	}

	m_information.setInformation(m_score, m_sonicPtr->getLive(),
		setTimeToPrint(), m_level);
}
//-----------------------------------------------------------------------------
void Controller::resetData()
{
	//if the player lose 3 lives, game over. 
	//reset all data
	if (m_gameOver) {
		m_score = RESET;
		m_currCoinPlayer = RESET;
		m_level = FIRST_LEVEL;
		m_board.resetDataBoard(true); //reset full data and back to first level -  with true bool
	}
	else
	{
		m_sonicLive = m_sonicPtr->getLive();
		m_board.resetDataBoard(false);
	}

	for (auto movable : m_movables)
		m_world.DestroyBody(movable->getBody());

	m_movables.clear();
	m_levelClock.restart();
	m_deltaClock.restart();
}
//-----------------------------------------------------------------------------
void Controller::ScanObjectLevel()
{
	m_board.setWorld(&m_world);
	m_board.scanMap();
	m_board.scanObjectsIconToMap();
	scanObjectsIconToMap();
	m_sonicPtr = &dynamic_cast<SonicPlayer&>(*m_movables[getSonicIndex()]);

	if (!m_gameOver)
		m_sonicPtr->setLive(m_sonicLive);

	setBackGround();
}
//-----------------------------------------------------------------------------
int Controller::setTimeToPrint()
{
	return (int)m_levelClock.getElapsedTime().asSeconds();
}
//-----------------------------------------------------------------------------
void Controller::clearTrashObjects()
{
	for (auto& movable : m_movables)
	{
		if (movable->isDisposed())
			m_world.DestroyBody(movable->getBody());
	}
	std::experimental::erase_if(m_movables, [](auto& movable)
		{
			return movable->isDisposed();
		});
}
//-----------------------------------------------------------------------------
void Controller::setBackGround()
{
	sf::Texture backGround;

	switch (m_level)
	{
	default:
		m_backGround.setTexture(ResourcesImages::getInstance().
			getTexture(ResourcesImages::imageType::BackGroundLevel1));
		break;
	case 2:
		m_backGround.setTexture(ResourcesImages::getInstance().
			getTexture(ResourcesImages::imageType::BackGroundLevel2));
		break;
	case 3:
		m_backGround.setTexture(ResourcesImages::getInstance().
			getTexture(ResourcesImages::imageType::BackGroundLevel3));
		break;
	case 4:
		m_backGround.setTexture(ResourcesImages::getInstance().
			getTexture(ResourcesImages::imageType::BackGroundLevel4));
		break;

	}
}
//-----------------------------------------------------------------------------
int Controller::getSonicIndex()const
{
	auto counter = 0;

	for (auto& movable : m_movables)
	{
		if (typeid(*movable) == typeid(SonicPlayer))
			return counter;

		counter++;
	}
	return counter;
}
//-----------------------------------------------------------------------------
void Controller::clicButton(ScreenButtons::typeButton task)
{
	switch (task)
	{
	case ScreenButtons::typeButton::b_soundOnButton:
		ResourcesSounds::getInstance().setValume(10.f);
		break;

	case ScreenButtons::typeButton::b_soundOffButton:
		ResourcesSounds::getInstance().setValume(0.f);
		break;


	case ScreenButtons::typeButton::b_pauseButton:

		sf::Sprite sprite;
		auto x = m_sonicPtr->getSprite().getPosition().x;

		sprite.setTexture(ResourcesImages::getInstance().
			getTexture(ResourcesImages::imageType::PressEnterToPlay));

		sprite.setOrigin(sprite.getTextureRect().width / 2.f,
			sprite.getTextureRect().height / 2.f);
		if (m_sonicPtr->getSprite().getPosition().x < m_window.getSize().x / 2.f)
			x = 550.f;

		sprite.setPosition(x + (OBJECT_SIZE * 2.f) , m_sonicPtr->getSprite().
			getPosition().y - (OBJECT_SIZE * 4.f));
		
		m_window.draw(sprite);
		m_window.display();

		bool gamePause = true;
		sf::Time timer = {};

		//wait the player press ENTER on keyboard to continue
		while (gamePause == true)
		{
			timer += m_deltaClock.restart();

			if (timer.asSeconds() > 0.01f) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
					gamePause = false;
				}
			}
		}
		break;
	}
}
//-----------------------------------------------------------------------------
void Controller::setDataLocationScreen()
{
	auto viewSize = sf::Vector2f(m_window.getSize());
	sf::Vector2f playerLocation = { m_sonicPtr->getSprite().getPosition().x,
		m_sonicPtr->getSprite().getPosition().y };

	if (playerLocation.x < ((viewSize.x - 250.f) / 2.f))
		playerLocation.x = ((viewSize.x - 250.f) / 2.f);

	playerLocation.y -= 100;

	auto view = sf::View(playerLocation, { viewSize.x - (OBJECT_SIZE * 4.f) ,viewSize.y - (OBJECT_SIZE * 2.f) });

	m_backGround.setOrigin(m_backGround.getGlobalBounds().width / 2.f,
		m_backGround.getGlobalBounds().height / 2.f);

	m_backGround.setTextureRect(sf::IntRect(0, 0, m_window.getSize().x, m_window.getSize().y));
	m_backGround.setPosition(playerLocation.x, playerLocation.y);
	m_window.setView(view);
	m_information.setPosition(m_window.getSize(), view.getCenter());
	m_buttons.setLocationButtons(m_window , view.getCenter());

}
