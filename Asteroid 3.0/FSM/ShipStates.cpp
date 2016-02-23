#include "ShipStates.h"

namespace fsm { namespace state {

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
		if (controller->GetAsteroids().size() == 0 || !controller->GetClosestAsteroid())
		{
			controller->GetFSM()->ChangeState(Idle::Instance());
			return;
		}

		if (controller->DistToAsteroid() <= MIN_DISTANCE_ASTEROID)	// if closest asteroid is too close
			controller->GetFSM()->ChangeState(Evade::Instance());
		else if (controller->CanShoot())												// if target is in line of sight
			controller->GetFSM()->ChangeState(Attack::Instance());
		else
		{
			float currentAngle = controller->ShipAngle();
			float targetAngle = controller->AngleToTarget();

			if (targetAngle > currentAngle)
			{
				if (utils::Abs(currentAngle - targetAngle) < 180.0f)
					controller->GetShip()->Steer(1.0f);
				else
					controller->GetShip()->Steer(-1.0f);
			}
			else
			{
				if (utils::Abs(currentAngle - targetAngle) < 180.0f)
					controller->GetShip()->Steer(-1.0f);
				else
					controller->GetShip()->Steer(1.0f);
			}
			controller->GetShip()->Thrust(1.0f);
		}
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
		// if we have gotten far enough away
		if (controller->DistToAsteroid() >= MIN_DISTANCE_ASTEROID * 1.3f)
			controller->GetFSM()->ChangeState(state::Idle::Instance());

		float currentAngle = controller->ShipAngle();
		float targetAngle = controller->AngleToTarget();

		// if we are not facing asteroid, steer away and thrust forward
		if (utils::Abs(currentAngle - targetAngle) > MIN_ANGLE_TO_BACK)
		{
			if (targetAngle > currentAngle)
			{
				if (utils::Abs(currentAngle - targetAngle) < 180.0f)
					controller->GetShip()->Steer(-1.0f);
				else
					controller->GetShip()->Steer(1.0f);
			}
			else
			{
				if (utils::Abs(currentAngle - targetAngle) < 180.0f)
					controller->GetShip()->Steer(1.0f);
				else
					controller->GetShip()->Steer(-1.0f);
			}
			controller->GetShip()->Thrust(1.0f);
		}
		else // thrust backward
			controller->GetShip()->Thrust(-1.0f);
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

	void Attack::Enter(FSMController* controller)
	{
		std::cout << "Entered Attack State" << std::endl;
	}

	void Attack::Execute(FSMController* controller)
	{
		// if we are unable to shoot, stay idle
		if (!controller->CanShoot())
		{
			controller->GetFSM()->ChangeState(state::Idle::Instance());
			return;
		}

		controller->GetShip()->Shoot();
	}

	void Attack::Exit(FSMController* controller)
	{

	}
}}