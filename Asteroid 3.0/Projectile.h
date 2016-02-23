#pragma once
#include "GameObject.h"

#define PROJECTILE_LIFE_TIME 0.5f

class Projectile : public GameObject
{
	sf::Clock m_Life;
public:
	Projectile(const sf::Vector2f& position, const sf::Vector2f& direction);		// constructor
	bool IsDead() const { return m_Life.getElapsedTime().asSeconds() >= PROJECTILE_LIFE_TIME; }
};