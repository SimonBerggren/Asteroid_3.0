#pragma once
#include <vector>
#include "FState.h"

namespace fusm
{
	template<class Controller>
	class FStateMachine
	{
		Controller* m_Controller;
		std::vector<state::FState<Controller>*> m_States;
		std::vector<state::FState<Controller>*> m_ActiveStates;

	public:
		FStateMachine(Controller* controller)
			: m_Controller(controller) { }

		void Update()
		{
			for (int i = 0; i < m_States.size(); ++i)
			{
				if (m_States[i]->IsActive())			// if state is active
				{
					m_States[i]->Enter();			// add it to active states
					m_ActiveStates.push_back(m_States[i]);
					m_States.erase(m_States.begin() + i);
				}
			}

			// highest activationlevel will be updated last = make a difference
			std::sort(m_ActiveStates.begin(), m_ActiveStates.end());

			for (int i = 0; i < m_ActiveStates.size(); ++i)
			{
				if (m_ActiveStates[i]->IsActive())
					m_ActiveStates[i]->Execute();
				else											// if state is not active
				{
					m_ActiveStates[i]->Exit();		// remove it from active states
					m_States.push_back(m_ActiveStates[i]);
					m_ActiveStates.erase(m_ActiveStates.begin() + i);
				}
			}
		}

		void AddState(state::FState<Controller>* state)
		{
			m_States.push_back(state);
		}
	};
}