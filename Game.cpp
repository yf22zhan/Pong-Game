#include "Game.h"

void Game::start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");

	SFMLSoundProvider soundProvider;
	ServiceLocator::registerServiceLocator(&soundProvider);
	ServiceLocator::getAudio()->playSong("audio/Soundtrack.ogg", true);

	PlayerPaddle *player1 = new PlayerPaddle();
	player1->setPosition((SCREEN_WIDTH/2), 700);

	AIPaddle *playerAI = new AIPaddle();
	playerAI->setPosition((SCREEN_WIDTH / 2), 40);

	GameBall *ball = new GameBall();
	ball->setPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);

	PangText *pangText = new PangText();

	_gameObjectManager.add("Paddle1", player1);
	_gameObjectManager.add("Paddle2", playerAI);
	_gameObjectManager.add("Ball", ball);
	_gameObjectManager.add("Text", pangText);
	_gameState = Game::ShowingSplash;

	gameLoop();

	_mainWindow.close();
}

const GameObjectManager& Game::getGameObjectManager()
{
	return _gameObjectManager;
}

bool Game::isExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::gameLoop()
{
	sf::Event currentEvent;

	while (!isExiting())
	{
		switch (_gameState)
		{
			case Game::ShowingSplash:
			{
				showSplashScreen();
				break;
			}
			case Game::ShowingMenu:
			{
				showMenu();
				break;
			}
			case Game::Playing:
			{
				while (_mainWindow.pollEvent(currentEvent))
				{
					if (currentEvent.type == sf::Event::Closed)
						_gameState = Game::Exiting;

					if (currentEvent.type == sf::Event::KeyPressed)
					{
						if (currentEvent.key.code == sf::Keyboard::Key::Escape)
							showMenu();
						//Used for debugging; display paddle position
						/*if (currentEvent.key.code == sf::Keyboard::Key::Q)
						{
							float pos = _gameObjectManager.get("Paddle1")->getPosition().x;
							std::cout << "x position: " << pos << std::endl;
						}*/
					}
				}

				_mainWindow.clear(sf::Color(0, 0, 0));

				_gameObjectManager.updateAll();
				_gameObjectManager.drawAll(_mainWindow);

				_mainWindow.display();

				break;
			}
		}
	}
}

void Game::showSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::showMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		_gameObjectManager.resetClock();
		break;
	case MainMenu::Nothing:
		_gameState = Game::ShowingMenu;
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;