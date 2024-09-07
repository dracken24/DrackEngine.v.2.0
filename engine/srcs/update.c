# include "../includes/engine.h"

void    draw(void)
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    DrawText("Welcome to the", 460, 250, 40, BLACK);
    DrawText("       DrackEngine       ", 250, 320, 60, BLACK);
    
    EndDrawing();
}

void    dr_update(Engine *engine)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        engine->exitCt = true;
    }

    draw();
}
