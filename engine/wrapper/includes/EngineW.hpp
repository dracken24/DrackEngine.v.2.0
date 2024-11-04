#pragma once

#include "../../core/includes/engine.h"
#include "../../core/includes/struct_globale.h"

namespace DrackEngine
{
	class EngineW
	{
		private:
			Engine w_engine;
			CoreInfos coreInfos;
			bool w_isInitialized;

		public:
			EngineW();
			~EngineW();

			bool Init();
			void Update();
			void Shutdown();
			
			// Getters
			bool		IsRunning() const { return w_isInitialized && !w_engine.exitCt; }
			CoreInfos*	GetCoreInfos() { return &coreInfos; }
			Engine*		GetCoreEngine() { return &w_engine; }
	};
};
