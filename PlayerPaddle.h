#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle :
	public VisibleGameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void update(float elapsedTime);
	void draw(sf::RenderWindow& rw);

	float getVelocity() const;

private:
	float _velocity;  // -- left ++ right
	float _maxVelocity;
};