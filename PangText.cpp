#include "PangText.h"

PangText::PangText() :
	_score(0)
{
	bool isLoaded =_font.loadFromFile("font/sansation.ttf");
	assert(isLoaded);

	_text.setFont(_font);
	_text.setCharacterSize(20);
	_text.setStyle(sf::Text::Bold);
	_text.setColor(sf::Color::White);
}

PangText::~PangText()
{
}

void PangText::draw(sf::RenderWindow & rw)
{
	rw.draw(_text);
}

sf::Text& PangText::getText()
{
	return _text;
}

int PangText::getScore() const
{
	return _score;
}

void PangText::incrementScore()
{
	_score++;
}

void PangText::resetScore()
{
	_score = 0;
}