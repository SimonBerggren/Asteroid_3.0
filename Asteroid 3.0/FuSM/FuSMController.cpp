#include "FuSMController.h"

namespace fusm
{
	FuSMController::FuSMController(Ship * ship, std::vector<Asteroid*>& asteroids)
		: Controller(ship, asteroids)
	{
		m_FuSM = new fusm::FStateMachine<FuSMController>(this);
	}
	void FuSMController::Update()
	{
		m_FuSM->Update();

		FindClosestAsteroid();
	}
}