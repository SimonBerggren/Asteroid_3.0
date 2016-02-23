#pragma once
#include "Asteroid.h"
#include "Ship.h"

#define PRINT_STATES							1			// print entering / exiting states

#define MIN_APPROACH_DISTANCE		200.0f		// minimum distance between target and ship before starting to approach
#define MIN_SHOOTING_DISTANCE		400.0f		// minimum distance before shooting become available
#define MIN_DISTANCE_ASTEROID		300.0f		// minimum distance before starting to evade asteroid instead of chasing it
#define MIN_ANGLE_TO_STEER			3.0f			// minimum angle between asteroid and ship before starting to steer
#define MIN_ANGLE_TO_BACK			10.0f			// minimum angle between asteroid and ship before starting to thrust backwards

class Controller
{
	Ship* m_Ship;											// ship to control
	Asteroid* m_ClosestAsteroid;						// asteroid closest to ship
	std::vector<Asteroid*>& m_Asteroids;		// reference to asteroids for being able to "see" them

public:
	Controller(Ship* ship, std::vector<Asteroid*>& asteroids);

	virtual void Update() = 0;			// updates controller
	void FindClosestAsteroid();			// searches asteroids for target
	float DistToAsteroid() const;		// returns current distance to target
	bool CanShoot() const;				// if target is in line of sight
	float AngleToTarget() const;			// current angle to target, in degrees
	float AngleDifference() const;		// difference of angles between ship and target, in degrees
	float ShipAngle() const;				// angle of ship's direction, in degrees

	std::vector<Asteroid*>& GetAsteroids() const { return m_Asteroids; }
	Asteroid* GetClosestAsteroid() const { return m_ClosestAsteroid; }
	Ship* GetShip() const { return m_Ship; }
};