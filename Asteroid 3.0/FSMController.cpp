#include "FSMController.h"
#include "ShipStates.h"

FSMController::FSMController(Ship * ship, std::vector<Asteroid*>& asteroids)
	: m_Ship(ship), m_Asteroids(asteroids)
{
	m_FSM = new StateMachine<FSMController>(this);
	m_FSM->ChangeState(state::Idle::Instance());
	m_ClosestAsteroid = nullptr;
}

void FSMController::Update()
{
	m_FSM->Update();
}

void FSMController::FindClosestAsteroid()
{
	for (int i = 0; i < m_Asteroids.size(); ++i)
	{
		if (utils::vec::Distance(m_Ship->getPosition(), m_Asteroids[i]->getPosition()) < DistToAsteroid())
			m_ClosestAsteroid = m_Asteroids[i];
	}
}

float FSMController::DistToAsteroid() const
{
	if (m_ClosestAsteroid)
		return utils::vec::Distance(m_Ship->getPosition(), m_ClosestAsteroid->getPosition());
	else
		return std::numeric_limits<float>::max();
}

bool FSMController::CanShoot() const
{
	return false;
}
