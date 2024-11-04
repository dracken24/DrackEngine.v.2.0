#ifndef ENGINEW_HPP
# define ENGINEW_HPP

#include "../../core/includes/engine.h"
#include "../../core/includes/struct_globale.h"

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

#endif
