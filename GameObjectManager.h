#pragma once
#pragma once
#include "VisibleGameObject.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, VisibleGameObject* gameObject);
	void remove(std::string name);
	int getObjectCount() const;
	VisibleGameObject* get(std::string name) const;

	void resetClock();
	void drawAll(sf::RenderWindow& renderWindow);
	void updateAll();

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;
	sf::Clock clock;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};