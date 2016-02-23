#include "FShipStates.h"

namespace fusm {
	namespace state {

		////////////////////////////////// IDLE STATE /////////////////////////////////////////

		void Idle::Enter()
		{
#if PRINT_STATES
			utils::Print("Entered idle state");
#endif
		}

		void Idle::Execute()
		{
			m_Controller->FindClosestAsteroid();
		}

		void Idle::Exit()
		{
#if PRINT_STATES
			utils::Print("Exited idle state");
#endif
		}

		float Idle::GetCurrentLevel()
		{
			SetCurrentLevel(!(bool)m_Controller->GetClosestAsteroid());			// 1 if no target, 0 otherwise
			return m_CurrentLevel;
		}

		////////////////////////////////// APPROACH STATE /////////////////////////////////////////

		void Approach::Enter()
		{
#if PRINT_STATES
			utils::Print("Entered approach state");
#endif
		}

		void Approach::Execute()
		{
			float currentAngle = m_Controller->ShipAngle();
			float targetAngle = m_Controller->AngleToTarget();

			if (m_CurrentLevel > 0.8f)
				m_Controller->GetShip()->Thrust(1.0f);

			if (utils::Abs(currentAngle - targetAngle) < MIN_ANGLE_TO_STEER)
				return;

			if (targetAngle > currentAngle)
			{
				if (utils::Abs(currentAngle - targetAngle) < 180.0f)
					m_Controller->GetShip()->Steer(1.0f);
				else
					m_Controller->GetShip()->Steer(-1.0f);
			}
			else
			{
				if (utils::Abs(currentAngle - targetAngle) < 180.0f)
					m_Controller->GetShip()->Steer(-1.0f);
				else
					m_Controller->GetShip()->Steer(1.0f);
			}
		}

		void Approach::Exit()
		{
#if PRINT_STATES
			utils::Print("Exited approach state");
#endif
		}

		float Approach::GetCurrentLevel()
		{
			// if there is no target, return 0
			if (m_Controller->GetClosestAsteroid())
			{
				SetCurrentLevel(m_Controller->DistToAsteroid() / MIN_APPROACH_DISTANCE);
				return m_CurrentLevel;
			}
		}

		////////////////////////////////// EVADE STATE /////////////////////////////////////////

		void Evade::Enter()
		{
#if PRINT_STATES
			utils::Print("Entered evade state");
#endif
		}

		void Evade::Execute()
		{
			float currentAngle = m_Controller->ShipAngle();
			float targetAngle = m_Controller->AngleToTarget();

			// if we are not facing asteroid, steer away and thrust forward
			if (utils::Abs(currentAngle - targetAngle) > MIN_ANGLE_TO_BACK)
			{
				if (targetAngle > currentAngle)
				{
					if (utils::Abs(currentAngle - targetAngle) < 180.0f)
						m_Controller->GetShip()->Steer(-1.0f);
					else
						m_Controller->GetShip()->Steer(1.0f);
				}
				else
				{
					if (utils::Abs(currentAngle - targetAngle) < 180.0f)
						m_Controller->GetShip()->Steer(1.0f);
					else
						m_Controller->GetShip()->Steer(-1.0f);
				}
				m_Controller->GetShip()->Thrust(1.0f);
			}
			else // thrust backward
				m_Controller->GetShip()->Thrust(-1.0f);
		}

		void Evade::Exit()
		{
#if PRINT_STATES
			utils::Print("Exited evade state");
#endif
		}

		float Evade::GetCurrentLevel()
		{
			SetCurrentLevel(1.0f - (m_Controller->DistToAsteroid() / MIN_DISTANCE_ASTEROID));
			return m_CurrentLevel;
		}

		////////////////////////////////// ATTACK STATE /////////////////////////////////////////

		void Attack::Enter()
		{
#if PRINT_STATES
			utils::Print("Entered attack state");
#endif
		}

		void Attack::Execute()
		{
			m_Controller->GetShip()->Shoot();
		}

		void Attack::Exit()
		{
#if PRINT_STATES
			utils::Print("Exited attack state");
#endif
		}

		float Attack::GetCurrentLevel()
		{
			if (m_Controller->CanShoot())
				SetCurrentLevel(1.0f);				// 0 if unable to shoot, 1 otherwise
			else
				SetCurrentLevel(0.0f);

			return m_CurrentLevel;
		}
	}
}