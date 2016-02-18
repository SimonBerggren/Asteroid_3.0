#pragma once
#include "State.h" 

template<class Owner>
class StateMachine
{
	StateMachine() = delete;
	StateMachine(const StateMachine&) = delete;

	Owner* owner;						// owner of finite state machine
	State<Owner>* currState;		// current state of owner
	State<Owner>* prevState;		// previous state of owner

public:
	StateMachine(Owner* owner)													// constructor
		: owner(owner), currState(nullptr), prevState(nullptr) { }
	virtual ~StateMachine() {}														// destructor

	// updates current state
	void Update()
	{
		if (currState)
			currState->Execute(owner);
	}

	// changes state of finite state machine
	void ChangeState(State<Owner>* newState)
	{
		if (prevState)
			prevState = currState;

		if (currState)
			currState->Exit(owner);

		currState = newState;

		currState->Enter(owner);
	}

	// goes back to previous state
	void GoToPrevState()
	{
		ChangeState(prevState);
	}

	// check if state machine is in specific state
	template <class State>
	bool IsInState()
	{
		return dynamic_cast<State*>(currState);
	}

	State<Owner>* CurrentState() const { return currState; }
	State<Owner>* PrevState() const { return prevState; }
};