#pragma once
#include "SFML/Graphics.hpp"
#include "VisibleGameObject.h"

class PangText :
	public VisibleGameObject
{
public:
	PangText();
	~PangText();

	void draw(sf::RenderWindow& rw);

	sf::Text& getText();
	int getScore() const;
	void incrementScore();
	void resetScore();

private:
	sf::Font _font;
	sf::Text _text;
	int _score;
};