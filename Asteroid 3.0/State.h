#pragma once

template<class Owner>
struct State
{
	virtual void Enter(Owner*) = 0;			// called once when entering state
	virtual void Execute(Owner*) = 0;		// called when within state
	virtual void Exit(Owner*) = 0;				// called once when exiting state
};