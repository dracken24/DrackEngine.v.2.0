#ifndef EVENTSW_HPP
# define EVENTSW_HPP

#include "../../core/includes/engine.h"
#include "../../../../library/extern/raylib/src/raylib.h"

class Events
{
    public:
        static void processEvents(Engine* engine);
        static bool isKeyPressed(int key);
        static bool isMouseButtonPressed(int button);
        static Vector2 getMousePosition();
};

#endif
