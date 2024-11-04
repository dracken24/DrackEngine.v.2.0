#include "../includes/EventsW.hpp"

using namespace DrackEngine;

void Events::processEvents(Engine* engine)
{
    window_events(engine);
}

bool Events::isKeyPressed(int key)
{
    return IsKeyPressed(key);
}

bool Events::isMouseButtonPressed(int button)
{
    return IsMouseButtonPressed(button);
}

Vector2 Events::getMousePosition()
{
    return GetMousePosition();
}
