#pragma once
#include "visiblegameobject.h"

class AIPaddle :
	public VisibleGameObject
{
public:
	AIPaddle(void);
	~AIPaddle(void);

	void update(float elapsedTime);
	void draw(sf::RenderWindow& rw);
};