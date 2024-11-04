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

#include "../includes/EngineW.hpp"
#include "../includes/EventsW.hpp"
#include "../includes/UpdateW.hpp"
#include "../includes/UIW.hpp"

int main()
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

    DE_DEBUG("Engine shutdown");
    return 0;
}

// #define _XOPEN_SOURCE 700

// # include "includes/Engine.hpp"
// # include "../../library/drackengine_lib/drackengine_lib.h"
// # include "../../library/drackengine_lib/utility/colors.h"
// # include "../includes/temp_for_build.h"
// # include "memory/dmemory.h"

// // Déclaration globale de l'engine
// Engine *g_engine = NULL;

// void test_log(void);

// int main(void)
// {
//     Engine engine;
//     g_engine = &engine;

//     CoreInfos coreInfos;
//     // ViewState currentView = STATE_VIEW_ENGINE;

//     initialize_memory();
//     dr_init(&engine, &coreInfos);
//     print_memory_usage("INIT");
//     // test_log();

//     while (!engine.exitCt)
//     {
//         dr_update(&engine, &coreInfos);
//         if (IsKeyPressed(KEY_M))
//         {
//             print_memory_usage("Update");
//         }
//     }

//     dr_exit(&engine, &coreInfos);
//     shutdown_memory();
//     print_memory_usage("EXIT");

//     return 0;
// }
