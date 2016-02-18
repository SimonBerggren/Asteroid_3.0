#pragma once
#include "FSMController.h"
#include "ShipStates.h"
#include "Projectile.h"
#include "Asteroid.h"
#include "Utilities.h"

#define PRE_GAME_TIME		1.0f		// time before game starts
#define MIN_SPAWN_TIME		5.0f		// minimum time between asteroid spawns
#define MAX_SPAWN_TIME		2.5f		// maximum time between asteroid spawns
#define SPAWN_TICK				0.5f		// how much spawn time is decreasing for each new asteroid

class GameSession
{
	sf::Clock m_PreGameTimer;							// timer before game starts
	float m_SpawnTime = MAX_SPAWN_TIME;		// current time between asteroid spawns
	sf::Clock m_SpawnTimer;								// keeps check of when to spawn a new asteroid

	FSMController* m_Controller;								// controls ship
	Ship* m_Ship;												// controlled by AI
	std::vector<Asteroid*> m_Asteroids;				// asteroids in game
	std::vector<Projectile*> m_Projectiles;			// projectiles in game

public:
	GameSession();										// constructor
	~GameSession();									// destructor

	void Update(float delta);							// updates game logic
	void Draw();											// draws all active game objects

private:
	void SpawnAsteroid();							// spawns a new asteroid randomly outside window
	void CheckCollisions();							// check collisions between player and asteroids as well as asteroids and projectiles
	void Init();												// initialize new game session
	void Clear();											// clear session of all objects
};