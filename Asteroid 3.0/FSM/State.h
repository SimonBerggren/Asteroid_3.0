#pragma once

namespace fsm
{
	template<class Controller>
	struct State
	{
		virtual void Enter(Controller*) = 0;			// called once when entering state
		virtual void Execute(Controller*) = 0;		// called when within state
		virtual void Exit(Controller*) = 0;			// called once when exiting state
	};
}