#include "Asteroid.h"

Asteroid::Asteroid(const sf::Vector2f& position)
	: GameObject(*textures::Asteroid(), position)
{
	// get random direction and speed
	float angle = utils::rnd::Float(0.0f, 360.0f);
	m_Direction = utils::vec::FromDegrees(angle);
	m_Speed = utils::rnd::Float(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
}

void Asteroid::Update(float delta)
{
	GameObject::Update(delta);
	rotate(m_Speed);
}