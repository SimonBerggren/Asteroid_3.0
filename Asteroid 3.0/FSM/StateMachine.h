#pragma once
#include "State.h" 

namespace fsm
{
	template<class Controller>
	class StateMachine
	{
		StateMachine() = delete;
		StateMachine(const StateMachine&) = delete;

		Controller* m_Controller;						// controller of finite state machine
		State<Controller>* m_CurrentState;		// current state of owner
		State<Controller>* m_PreviousState;		// previous state of owner

	public:
		StateMachine(Controller* controller)
			: m_Controller(controller), m_CurrentState(nullptr), m_PreviousState(nullptr) { }

		void Update()																// updates current state
		{
			if (m_CurrentState)
				m_CurrentState->Execute(m_Controller);
		}

		void ChangeState(State<Controller>* newState)			// changes state of state machine
		{
			if (m_PreviousState)
				m_PreviousState = m_CurrentState;

			if (m_CurrentState)
				m_CurrentState->Exit(m_Controller);

			m_CurrentState = newState;

			m_CurrentState->Enter(m_Controller);
		}
			
		void GoToPrevState()													// goes back to previous state
		{
			ChangeState(m_PreviousState);
		}
			
		template <class State>												// check if state machine is in specific state
		bool IsInState()
		{
			return dynamic_cast<State*>(m_CurrentState);
		}

		State<Controller>* CurrentState() const { return m_CurrentState; }
		State<Controller>* PrevState() const { return m_PreviousState; }
	};
}