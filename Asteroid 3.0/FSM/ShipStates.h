#pragma once
#include "FSMController.h"

namespace fsm { namespace state
{
	////////////////////////////////// IDLE STATE /////////////////////////////////////////

	class Idle : public State<FSMController>
	{
	private:
		Idle() {}

		Idle(const Idle&) = delete;
		Idle& operator=(const Idle&) = delete;

	public:
		static Idle* Instance();

		virtual void Enter(FSMController*) override;
		virtual void Execute(FSMController*) override;
		virtual void Exit(FSMController*) override;
	};

	////////////////////////////////// APPROACH STATE /////////////////////////////////////////

	class Approach : public State<FSMController>
	{
	private:
		Approach() {}

		Approach(const Approach&) = delete;
		Approach& operator=(const Approach&) = delete;

	public:
		static Approach* Instance();

		virtual void Enter(FSMController*) override;
		virtual void Execute(FSMController*) override;
		virtual void Exit(FSMController*) override;
	};

	////////////////////////////////// EVADE STATE /////////////////////////////////////////

	class Evade : public State<FSMController>
	{
	private:
		Evade() {}

		Evade(const Evade&) = delete;
		Evade& operator=(const Evade&) = delete;

	public:
		static Evade* Instance();

		virtual void Enter(FSMController*) override;
		virtual void Execute(FSMController*) override;
		virtual void Exit(FSMController*) override;
	};

	////////////////////////////////// ATTACK STATE /////////////////////////////////////////

	class Attack : public State<FSMController>
	{
	private:
		Attack() {}

		Attack(const Attack&) = delete;
		Attack& operator=(const Attack&) = delete;

	public:
		static Attack* Instance();

		virtual void Enter(FSMController*) override;
		virtual void Execute(FSMController*) override;
		virtual void Exit(FSMController*) override;
	};
}}