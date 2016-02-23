#pragma once
#include "StateMachine.h"
#include "../Controller.h"

namespace fsm
{
	class FSMController  : public Controller
	{
		StateMachine<FSMController>* m_FSM;		// finite state machine
	public:
		FSMController(Ship* ship, std::vector<Asteroid*>& asteroids);
		void Update() override;
		StateMachine<FSMController>* GetFSM() const { return m_FSM; }
	};
}