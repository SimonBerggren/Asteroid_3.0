#pragma once
#include "FuSMController.h"

namespace fusm { namespace state {

		////////////////////////////////// IDLE STATE /////////////////////////////////////////

		class Idle : public FState<FuSMController>
		{
			Idle() = delete;
			Idle(const Idle&) = delete;
		public:
			Idle(FuSMController* controller, float activationLevel) : FState(controller, activationLevel) { }

			void Enter() override;
			void Execute() override;
			void Exit() override;
			float GetCurrentLevel() override;
		};

		////////////////////////////////// APPROACH STATE /////////////////////////////////////////

		class Approach : public FState<FuSMController>
		{
			Approach() = delete;
			Approach(const Approach&) = delete;
		public:
			Approach(FuSMController* controller, float activationLevel) : FState(controller, activationLevel) { }

			void Enter() override;
			void Execute() override;
			void Exit() override;
			float GetCurrentLevel() override;
		};

		////////////////////////////////// EVADE STATE /////////////////////////////////////////

		class Evade : public FState<FuSMController>
		{
			Evade() = delete;
			Evade(const Evade&) = delete;
		public:
			Evade(FuSMController* controller, float activationLevel) : FState(controller, activationLevel) { }

			void Enter() override;
			void Execute() override;
			void Exit() override;
			float GetCurrentLevel() override;
		};

		////////////////////////////////// ATTACK STATE /////////////////////////////////////////

		class Attack : public FState<FuSMController>
		{
			Attack() = delete;
			Attack(const Attack&) = delete;
			Attack(const Attack&&) = delete;
		public:
			Attack(FuSMController* controller, float activationLevel) : FState(controller, activationLevel) { }

			void Enter() override;
			void Execute() override;
			void Exit() override;
			float GetCurrentLevel() override;
		};
}}