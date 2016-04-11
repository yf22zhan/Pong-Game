#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() :
	_velocity(0),
	_maxVelocity(600.0f)
{
	load("res/paddle.png");
	assert(isLoaded());

	getSprite().setOrigin(getWidth() / 2, getHeight() / 2);
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::draw(sf::RenderWindow & rw)
{
	VisibleGameObject::draw(rw);
}

float PlayerPaddle::getVelocity() const
{
	return _velocity;
}

void PlayerPaddle::update(float elapsedTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		_velocity -= 3.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		_velocity += 3.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		_velocity = 0.0f;
	}

	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;


	sf::Vector2f pos = this->getPosition();

	if (pos.x <= getWidth() / 2)
	{
		this->setPosition(getWidth() / 2, 700);
		_velocity = -_velocity; // Bounce by current velocity in opposite direction
	}
	else if (pos.x >= (Game::SCREEN_WIDTH - getWidth() / 2))
	{
		this->setPosition((Game::SCREEN_WIDTH - getWidth() / 2), 700);
		_velocity = -_velocity; // Bounce by current velocity in opposite direction
	}

	//if ((pos.x <= getWidth() / 2) 
	//	|| (pos.x >= (Game::SCREEN_WIDTH - getWidth() / 2)))
	//{
	//	_velocity = -_velocity; // Bounce by current velocity in opposite direction
	//}

	getSprite().move(_velocity * elapsedTime, 0);
}