#include "FSMController.h"
#include "ShipStates.h"

namespace fsm
{
	FSMController::FSMController(Ship * ship, std::vector<Asteroid*>& asteroids)
		: Controller(ship, asteroids)
	{
		m_FSM = new StateMachine<FSMController>(this);
	}

	void FSMController::Update()
	{
		FindClosestAsteroid();
		m_FSM->Update();
	}
}