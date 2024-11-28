#pragma once

#include "../../core/includes/engine.h"
#include "../../core/includes/struct_globale.h"
#include "../srcs/UI/Buttons.hpp"
#include "../../../library/drackengine_lib/drackengine_lib.h"

#define ButtonsHPP DrackEngine::UI::Button

namespace DrackEngine
{
	typedef enum EngineButtonsEnum
	{
		PLAY,
		STOP,
	}	EngineButtonsEnum;

	class EngineButtons
	{
		public:
			EngineButtons(void);
			~EngineButtons(void);

			void	setPlayButton(void);
			void	setStopButton(void);
			void	setEngineRef(Engine *engine);

			void	DrawUpButtons(void);

		private:
			ButtonsHPP  play;
			ButtonsHPP  stop;

			Engine *engineRef;
	};

//******************************************************************************//

	class EngineW
	{
		public:
			EngineW();
			~EngineW();

			bool Init();
			void Update();
			void Shutdown();
			
			// Getters
			bool		IsRunning() const { return w_isInitialized && !w_engine.exitCt; }
			CoreInfos*	GetCoreInfos() { return &w_coreInfos; }
			Engine*		GetCoreEngine() { return &w_engine; }
			void		DrawUI();

			ButtonsHPP	GetButton(EngineButtonsEnum button);
		
		private:
		
		public:
			EngineButtons engineButtons;

		private:
			Engine w_engine;
			CoreInfos w_coreInfos;
			bool w_isInitialized;

			RenderTexture2D w_uiLayer;

			void	initButtonsMenuUp(void);
	};
};
