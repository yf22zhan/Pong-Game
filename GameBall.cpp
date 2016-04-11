#include "GameBall.h"
#include "Game.h"

GameBall::GameBall() :
	_velocity(230.0f),
	_elapsedTimeSinceStart(0.0f)
{
	load("res/ball.png");
	assert(isLoaded());

	getSprite().setOrigin(getWidth() / 2, getHeight() / 2);

	_angle = (float) (rand() % 361);
}

GameBall::~GameBall()
{
}

void GameBall::update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	PangText* pangText = dynamic_cast<PangText*>(Game::getGameObjectManager().get("Text"));
	pangText->getText().setPosition((Game::SCREEN_WIDTH / 2 - 100), (Game::SCREEN_HEIGHT / 2) - 100 - getHeight());

	// Delay game from starting until 3 seconds have passed
	if (_elapsedTimeSinceStart < 1.0f)
	{
		pangText->getText().setString("Game Start in 3 sec !");
		return;
	}
	if (_elapsedTimeSinceStart < 2.0f)
	{
		pangText->getText().setString("Game Start in 2 sec !");
		return;
	}
	if (_elapsedTimeSinceStart < 3.0f)
	{
		pangText->getText().setString("Game Start in 1 sec !");
		return;
	}

	pangText->getText().setPosition(0, 0);
	pangText->getText().setString("score: " + std::to_string(pangText->getScore()));

	float moveAmount = _velocity  * elapsedTime;
	float moveByX = linearVelocityX(_angle) * moveAmount;
	float moveByY = linearVelocityY(_angle) * moveAmount;


	//collide with the left or right side of the screen
	if (getPosition().x + moveByX <= 0 + getWidth() / 2
		|| getPosition().x + getWidth() / 2 + moveByX >= Game::SCREEN_WIDTH)
	{
		//Ricochet!
		_angle = 180.0f - _angle;

		if (_angle > -180.0f && _angle <= -170.0f) _angle += 20.0f;
		else if (_angle > 170.0f && _angle <= 180.0f) _angle -= 20.0f;
		else if (_angle > -10.0f && _angle <= 0.0f) _angle -= 20.0f;
		else if (_angle > 0.0f && _angle <= 10.0f) _angle += 20.0f;

		if (_angle < 0) _angle += 360.0f;
		moveByX = -moveByX;
	}

	//collide with PlayerPaddle
	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::getGameObjectManager().get("Paddle1"));
	if (player1 != NULL)
	{
		sf::Rect<float> p1BB = player1->getBoundingRect();

		if (p1BB.intersects(getBoundingRect()))       //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
		{
			_angle = 360.0f - _angle;

			moveByY = -moveByY;

			// Make sure ball isn't inside paddle
			if (getBoundingRect().top + getBoundingRect().height > player1->getBoundingRect().top)
			{
				setPosition(getPosition().x, player1->getBoundingRect().top - getHeight() / 2 - 1);
			}

			// Now add "English" based on the players velocity.  
			float playerVelocity = player1->getVelocity();

			if (playerVelocity < 0)
			{
				// moving left
				_angle -= 20.0f;
				if (_angle < 0) _angle += 360.0f;
			}
			else if (playerVelocity > 0)
			{
				_angle += 20.0f;
				if (_angle > 360.0f) _angle -= 360.0f;
			}

			_velocity += 5.0f;

			ServiceLocator::getAudio()->playSound("audio/blip.wav");
			pangText->incrementScore();
		}	
	}

	//collide with AIPaddle
	AIPaddle* playerAI = dynamic_cast<AIPaddle*>(Game::getGameObjectManager().get("Paddle2"));
	if (playerAI != NULL)
	{
		sf::Rect<float> p2BB = playerAI->getBoundingRect();

		if (p2BB.intersects(getBoundingRect()))       //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
		{
			_angle = 360.0f - _angle;

			moveByY = -moveByY;

			// Make sure ball isn't inside paddle
			if (getBoundingRect().top < (playerAI->getBoundingRect().top + playerAI->getBoundingRect().height))
			{
				setPosition(getPosition().x, playerAI->getBoundingRect().top + playerAI->getBoundingRect().height + getHeight() / 2 + 1);
			}
		}
	}
	
	// Fall off
	if (getPosition().y + getHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
	{
		// move to middle of the screen for now and randomize angle
		getSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
		_angle = (float)(rand() % 361);
		_velocity = 220.0f;
		_elapsedTimeSinceStart = 0.0f;
		pangText->resetScore();
	}

	getSprite().move(moveByX, moveByY);
}

float GameBall::linearVelocityX(float angle)
{
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::linearVelocityY(float angle)
{
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}

