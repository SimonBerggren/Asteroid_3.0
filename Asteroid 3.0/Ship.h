#pragma once

#include "Projectile.h"

#define SHIP_RELOAD_TIME	0.25f		// after each shot, we need to reload
#define SHIP_MAX_SPEED		7.5f		// maximum speed, works both forward and backward
#define SHIP_MIN_SPEED		0.1f		// while not within the limit, we apply friciton, otherwise breaks are applied
#define SHIP_FRICTION			0.99f		// friction applied when not thrusting
#define SHIP_STEER_POWER	5.0f		// how hard ship will turn

class Ship : public GameObject
{
	sf::Clock m_Reloading;										// reloading timer
	std::vector<Projectile*>& m_Projectiles;				// copy of projectiles so ship can shoot
public:
	Ship(std::vector<Projectile*>& projectiles);			// constructor
	void Update(float delta) override;						// overriding so we can apply friction
	void Steer(float val);											// values -1 to 1 = left to right
	void Thrust(float val);											// values -1 to 1 = backward to forward
	void Shoot();														// spawn a new projectile heading in the same direction ship is pointing to
	bool Reloading() const;										// if ship is ready to fire or not
};