#include "Ship.h"

Ship::Ship(std::vector<Projectile*>& projectiles)
	: GameObject(*textures::Ship(), sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f)), m_Projectiles(projectiles)
{

	m_Direction = utils::vec::FromRadians(getRotation());
}

void Ship::Update(float delta)
{
	// smooth stop
	if (m_Speed > SHIP_MIN_SPEED || m_Speed < -SHIP_MIN_SPEED)
		m_Speed *= SHIP_FRICTION;
	else
		m_Speed = 0.0f;

	GameObject::Update(delta);
}

void Ship::Steer(float val)
{
	val = utils::Clamp(val, -1.0f, 1.0f);
	rotate(val * SHIP_STEER_POWER);
	m_Direction = utils::vec::FromDegrees(getRotation());
}

void Ship::Thrust(float val)
{
	val = utils::Clamp(val, -1.0f, 1.0f);
	m_Speed = utils::Clamp(m_Speed + val, -SHIP_MAX_SPEED, SHIP_MAX_SPEED);
}

void Ship::Shoot()
{
	if (Reloading())
		return;

	m_Projectiles.push_back(new Projectile(getPosition(), m_Direction));
	m_Reloading.restart();
}

bool Ship::Reloading() const
{
	return m_Reloading.getElapsedTime().asSeconds() <= SHIP_RELOAD_TIME;
}