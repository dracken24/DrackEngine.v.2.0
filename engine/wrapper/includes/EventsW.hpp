/* =============================================================================== */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/*               -------------------------------------------------                 */
/*                PROJET: DrackEngine   PAR: Dracken24                             */
/*               -------------------------------------------------                 */
/*                CREATED: 05-12th-2024                                            */
/*                MODIFIED BY: Dracken24                                           */
/*                LAST MODIFIED: 05-12th-2024                                      */
/*               -------------------------------------------------                 */
/*                FILE: EventsW.hpp                                                */
/*               -------------------------------------------------                 */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/* =============================================================================== */

#pragma once

#include "../../core/includes/engine.h"
#include "../../../../library/extern/raylib/src/raylib.h"

namespace DrackEngine
{
    class Events
    {
        public:
            static void processEvents(Engine* engine);
            static bool isKeyPressed(int key);
            static bool isMouseButtonPressed(int button);
            static Vector2 getMousePosition();
    };
}
