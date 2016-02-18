#include "ShipStates.h"

namespace state
{
	////////////////////////////////// IDLE STATE /////////////////////////////////////////

	Idle* Idle::Instance()
	{
		static Idle instance;
		return &instance;
	}

	void Idle::Enter(FSMController * controller)
	{
		std::cout << "Entered Idle State" << std::endl;
	}

	void Idle::Execute(FSMController * controller)
	{
		// if there is no asteroids, wait
		if (controller->GetAsteroids().size() == 0)
			return;

		// if there is no asteroid in range, find one
		if (!controller->GetClosestAsteroid())
		{
			controller->FindClosestAsteroid();
			return;
		}

		if (controller->DistToAsteroid() < MIN_DISTANCE_ASTEROID)	// if closest asteroid is too close
			controller->GetFSM()->ChangeState(Evade::Instance());
		else if (controller->CanShoot())												// if target is in line of sight
			controller->GetFSM()->ChangeState(Attack::Instance());
		else																						// else approach target
			controller->GetFSM()->ChangeState(Approach::Instance());
	}

	void Idle::Exit(FSMController * controller)
	{

	}

	////////////////////////////////// APPROACH STATE /////////////////////////////////////////

	Approach* Approach::Instance()
	{
		static Approach instance;
		return &instance;
	}

	void Approach::Enter(FSMController * controller)
	{
		std::cout << "Entered Approaching State" << std::endl;
	}

	void Approach::Execute(FSMController * controller)
	{
		// if there is no asteroids, wait
		if (controller->GetAsteroids().size() == 0)
		{
			controller->GetFSM()->ChangeState(Idle::Instance());
			return;
		}

		if (controller->DistToAsteroid() < MIN_DISTANCE_ASTEROID)	// if closest asteroid is too close
			controller->GetFSM()->ChangeState(Evade::Instance());
		else if (controller->CanShoot())												// if target is in line of sight
			controller->GetFSM()->ChangeState(Attack::Instance());

		sf::Vector2f directionToTarget = utils::vec::Direction(controller->GetShip()->getPosition(), 
																					controller->GetClosestAsteroid()->getPosition());
		directionToTarget = utils::vec::Normalized(directionToTarget);
		float angleToTarget = utils::vec::ToDegrees(directionToTarget);
		//controller->GetShip()->Steer(angleToTarget);
		std::cout << angleToTarget << std::endl;
	}

	void Approach::Exit(FSMController * controller)
	{

	}

	////////////////////////////////// EVADE STATE /////////////////////////////////////////

	Evade* Evade::Instance()
	{
		static Evade instance;
		return &instance;
	}

	void Evade::Enter(FSMController * controller)
	{
		std::cout << "Entered Evade State" << std::endl;
	}

	void Evade::Execute(FSMController * controller)
	{

	}

	void Evade::Exit(FSMController * controller)
	{

	}

	////////////////////////////////// ATTACK STATE /////////////////////////////////////////

	Attack* Attack::Instance()
	{
		static Attack instance;
		return &instance;
	}

	void Attack::Enter(FSMController * controller)
	{
		std::cout << "Entered Attack State" << std::endl;
	}

	void Attack::Execute(FSMController * controller)
	{

	}

	void Attack::Exit(FSMController * controller)
	{

	}
}