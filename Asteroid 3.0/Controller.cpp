#include "Controller.h"

Controller::Controller(Ship* ship, std::vector<Asteroid*>& asteroids)
	: m_Ship(ship), m_Asteroids(asteroids)
{
	m_ClosestAsteroid = nullptr;
}

void Controller::FindClosestAsteroid()
{
	m_ClosestAsteroid = nullptr;
	for (int i = 0; i < m_Asteroids.size(); ++i)
	{
		if (utils::vec::Distance(m_Ship->getPosition(), m_Asteroids[i]->getPosition()) < DistToAsteroid())
			m_ClosestAsteroid = m_Asteroids[i];
	}
}

float Controller::DistToAsteroid() const
{
	if (m_ClosestAsteroid)
		return utils::vec::Distance(m_Ship->getPosition(), m_ClosestAsteroid->getPosition());
	else
		return std::numeric_limits<float>::max();
}

bool Controller::CanShoot() const
{
	return m_ClosestAsteroid && DistToAsteroid() <= MIN_SHOOTING_DISTANCE && 
		utils::Abs(ShipAngle() - AngleToTarget()) <= MIN_ANGLE_TO_STEER;
}

float Controller::AngleToTarget() const
{
	if (m_ClosestAsteroid)
	{
		sf::Vector2f directionToTarget = utils::vec::Direction(m_Ship->getPosition(), m_ClosestAsteroid->getPosition());
		return utils::vec::ToDegrees(directionToTarget);
	}
}

float Controller::AngleDifference() const
{
	if (m_ClosestAsteroid)
		return m_Ship->getRotation() - AngleToTarget();
}

float Controller::ShipAngle() const
{
	return utils::vec::ToDegrees(m_Ship->GetDirection());
}