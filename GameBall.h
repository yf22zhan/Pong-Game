#pragma once
#include "visiblegameobject.h"

class GameBall :
	public VisibleGameObject
{
public:
	GameBall();
	virtual ~GameBall();
	void update(float);

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;

	float linearVelocityX(float angle);
	float linearVelocityY(float angle);
};