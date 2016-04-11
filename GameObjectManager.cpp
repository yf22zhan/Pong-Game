#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}

void GameObjectManager::resetClock()
{
	clock.restart();
}

void GameObjectManager::drawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::updateAll()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr =
		_gameObjects.begin();
	float timeDelta = clock.getElapsedTime().asSeconds();
	clock.restart();

	while (itr != _gameObjects.end())
	{
		itr->second->update(timeDelta);
		itr++;
	}
}