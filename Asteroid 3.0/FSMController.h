#pragma once
#include "StateMachine.h"
#include "Asteroid.h"
#include "Ship.h"

#define MIN_DISTANCE_ASTEROID	-100.0f		// minimum distance before starting to evade asteroid instead of chasing it

class FSMController
{
	StateMachine<FSMController>* m_FSM;		// finite state machine
	Ship* m_Ship;											// ship to control
	Asteroid* m_ClosestAsteroid;						// asteroid closest to ship
	std::vector<Asteroid*>& m_Asteroids;		// reference to asteroids for being able to "see" them

public:
	FSMController(Ship* ship, std::vector<Asteroid*>& asteroids);			// constructor

	void Update();						// updates controller
	void FindClosestAsteroid();		// searches asteroids for closest
	float DistToAsteroid() const;	// returns current distance to target
	bool CanShoot() const;			// if target is in line of sight

	std::vector<Asteroid*>& GetAsteroids() const { return m_Asteroids; }
	StateMachine<FSMController>* GetFSM() const { return m_FSM; }
	Asteroid* GetClosestAsteroid() const { return m_ClosestAsteroid; }
	Ship* GetShip() const { return m_Ship; }
};