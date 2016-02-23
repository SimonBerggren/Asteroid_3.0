#include "DTController.h"

DTController::DTController(Ship * ship, std::vector<Asteroid*>& asteroids)
	: Controller(ship, asteroids)
{
}

void DTController::Update()
{
	if (!GetClosestAsteroid())
		Idle();
	else if (DistToAsteroid() <= MIN_DISTANCE_ASTEROID)
		Evade();
	else if (DistToAsteroid() > MIN_DISTANCE_ASTEROID)
		Approach();
}

void DTController::Idle()
{
	FindClosestAsteroid();
}

void DTController::Evade()
{
	float currentAngle = ShipAngle();
	float targetAngle = AngleToTarget();

	// if we are not facing asteroid, steer away and thrust forward
	if (utils::Abs(currentAngle - targetAngle) > MIN_ANGLE_TO_BACK)
	{
		if (targetAngle > currentAngle)
		{
			if (utils::Abs(currentAngle - targetAngle) < 180.0f)
				GetShip()->Steer(-1.0f);
			else
				GetShip()->Steer(1.0f);
		}
		else
		{
			if (utils::Abs(currentAngle - targetAngle) < 180.0f)
				GetShip()->Steer(1.0f);
			else
				GetShip()->Steer(-1.0f);
		}
		GetShip()->Thrust(1.0f);
	}
	else // thrust backward
		GetShip()->Thrust(-1.0f);

	if (CanShoot())
		Attack();
}

void DTController::Approach()
{
	float currentAngle = ShipAngle();
	float targetAngle = AngleToTarget();

	GetShip()->Thrust(1.0f);

	if (utils::Abs(currentAngle - targetAngle) < MIN_ANGLE_TO_STEER)
		return;

	if (targetAngle > currentAngle)
	{
		if (utils::Abs(currentAngle - targetAngle) < 180.0f)
			GetShip()->Steer(1.0f);
		else
			GetShip()->Steer(-1.0f);
	}
	else
	{
		if (utils::Abs(currentAngle - targetAngle) < 180.0f)
			GetShip()->Steer(-1.0f);
		else
			GetShip()->Steer(1.0f);
	}

	if (CanShoot())
		Attack();
}

void DTController::Attack()
{
	GetShip()->Shoot();
}