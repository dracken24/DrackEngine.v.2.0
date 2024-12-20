// /*******************************************************************************/
// /*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
// /* |            ------------------------------------------------             | */
// /* |            *--*  PROJET: DrackEngine   PAR: Dracken24  *--*             | */
// /* |            ------------------------------------------------             | */
// /* |            *--*  DATE:	  	    06-09-2024  	       *--*             | */
// /* |            ------------------------------------------------             | */
// /* |            *--*  FILE:           Main.cpp              *--*             | */
// /* |            ------------------------------------------------             | */
// /*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
// /*******************************************************************************/

#include "DrackEngine.hpp"

#include "../includes/EngineW.hpp"
#include "../includes/EventsW.hpp"
#include "../includes/UpdateW.hpp"
#include "../includes/UIW.hpp"

using namespace DrackEngine;

int main(int argc, char **argv)
{
    DE_DEBUG("Starting engine...");
    EngineW engine;
    
    DE_DEBUG("Checking initialization...");
    if (!engine.IsRunning())
    {
        DE_DEBUG("Failed to initialize engine 2");
        return 1;
    }

    print_memory_usage("INIT");

    DE_DEBUG("Entering main loop...");
    while (engine.IsRunning())
    {
        engine.Update();
        
        if (Events::isKeyPressed(KEY_M))
        {
            print_memory_usage("Update");
        }
    }
    DE_DEBUG("Exit Main loop");

    engine.Shutdown();

    DE_DEBUG("Engine shutdown");
    return 0;
}

// namespace DrackEngine {
//     namespace Core {
//         // Interfaces avec le code C
//     }
    
//     namespace UI {
//         // Composants UI
//     }
    
//     namespace Graphics {
//         // Système de rendu
//     }
    
//     namespace Utils {
//         // Utilitaires
//     }
// } // namespace DrackEngine
