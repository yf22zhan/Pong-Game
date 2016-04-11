#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"

AIPaddle::AIPaddle()
{
	load("res/paddle.png");
	assert(isLoaded());

	getSprite().setOrigin(getWidth() / 2, getHeight() / 2);
}

AIPaddle::~AIPaddle()
{
}

void AIPaddle::draw(sf::RenderWindow & rw)
{
	VisibleGameObject::draw(rw);
}

void AIPaddle::update(float elapsedTime)
{
	const GameBall* gameBall = static_cast<GameBall*>
		(Game::getGameObjectManager().get("Ball"));
	sf::Vector2f ballPosition = gameBall->getPosition();

	sf::Vector2f paddlePosition = this->getPosition();

	float dif = ballPosition.x - paddlePosition.x;

	if ((paddlePosition.x + dif) <= getWidth() / 2)
	{
		this->setPosition(getWidth() / 2, 40);
	}
	else if ((paddlePosition.x + dif) >= (Game::SCREEN_WIDTH - getWidth() / 2))
	{
		this->setPosition((Game::SCREEN_WIDTH - getWidth() / 2), 40);
	}
	else
	{
		getSprite().move(dif, 0);
	}
}