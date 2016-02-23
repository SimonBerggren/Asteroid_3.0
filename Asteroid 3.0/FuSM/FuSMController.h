#pragma once
#include "FStateMachine.h"
#include "../Controller.h"

namespace fusm
{
	class FuSMController : public Controller
	{
		FStateMachine<FuSMController>* m_FuSM;									// fuzzy state machine
	public:
		FuSMController(Ship* ship, std::vector<Asteroid*>& asteroids);
		void Update() override;
		FStateMachine<FuSMController>* GetFuSM() const { return m_FuSM; }
	};
}