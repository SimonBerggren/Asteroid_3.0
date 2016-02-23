#pragma once
#include "../Utilities.h"

namespace fusm { namespace state {

template<class Controller>
class FState
{
private:
	FState() = delete;
	FState(const FState&) = delete;

protected:
	Controller* m_Controller;
	float m_ActivationLevel;
	float m_CurrentLevel;

public:
	FState(Controller* controller, float activationLevel = 1.0f)
		: m_Controller(controller), m_ActivationLevel(activationLevel) { }

	virtual void Enter() = 0;							// called once when entering state
	virtual void Execute() = 0;						// called when within state
	virtual void Exit() = 0;							// called once when exiting state
	virtual float GetCurrentLevel() = 0;

	float GetActivationLevel() const { return m_ActivationLevel; }

	// set current level
	void SetCurrentLevel(float currentLevel) { m_CurrentLevel = utils::Clamp(currentLevel, 0.0f, 1.0f); }

	// has current level reached activation level?
	bool IsActive() { return GetCurrentLevel() > m_ActivationLevel; }

	friend bool operator<(const FState& lhs, const FState& rhs) { return (lhs.GetCurrentLevel() / lhs.GetActivationLevel()) < (rhs.GetCurrentLevel() / rhs.GetActivationLevel()); }
	friend bool operator> (const FState& lhs, const FState& rhs) { return rhs < lhs; }
	friend bool operator<=(const FState& lhs, const FState& rhs) { return !(lhs > rhs); }
	friend bool operator>=(const FState& lhs, const FState& rhs) { return !(lhs < rhs); }
};
}}