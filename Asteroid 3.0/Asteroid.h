#pragma once
#include "Projectile.h"

#define ASTEROID_MIN_SPEED 1.0f	// minimum speed
#define ASTEROID_MAX_SPEED 3.0f	// maximum speed

class Asteroid : public GameObject
{
public:
	Asteroid(const sf::Vector2f& position);			// constructor
	void Update(float delta) override;				// overrides update for continuous rotation
};