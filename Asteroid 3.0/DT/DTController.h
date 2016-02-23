#pragma once
#include "../Controller.h"

class DTController : public Controller
{
public:
	DTController(Ship* ship, std::vector<Asteroid*>& asteroids);
	void Update() override;

private:
	// tree methods
	void Idle();
	void Evade();
	void Approach();
	void Attack();
};