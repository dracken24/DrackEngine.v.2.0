# include "../includes/engine.h"

void    dr_init(Engine *engine)
{
    engine->exitCt = false;
    engine->screenSize = (Vector2){1200, 750};
    
    InitWindow(engine->screenSize.x, engine->screenSize.y, "DrackEngine");
	SetTargetFPS(60);
}
