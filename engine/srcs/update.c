/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 update.c               *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "../includes/engine.h"
# include "../includes/struct_globale.h"

void    draw_msg_intro(void)
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    Vector2 center_text = (Vector2){GetScreenWidth() / 2 - MeasureText("Welcome to the", 40) / 2, GetScreenHeight() / 2 - 75};
    Vector2 center_text2 = (Vector2){GetScreenWidth() / 2 - MeasureText("DrackEngine", 60) / 2, GetScreenHeight() / 2 - 20};

    DrawText("Welcome to the", center_text.x, center_text.y, 40, BLACK);
    DrawText("DrackEngine", center_text2.x, center_text2.y, 60, BLACK);
    
    EndDrawing();
}

void    input_events(Engine *engine)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        engine->exitCt = true;
    }
    if (IsKeyPressed(KEY_M))
    {
        print_memory_usage("Update");
    }
}

void    adjust_menu_camera(Engine *engine)
{
    DE_DEBUG("Adjust Menu Camera");

    Vector2 diff = (Vector2){engine->screenSize.x - engine->lastScreenSize.x, engine->screenSize.y - engine->lastScreenSize.y};

    Rectangle rec00 = engine->allCameras->camera00.rectForCam;
    Rectangle rec01 = engine->allCameras->camera01.rectForCam;
    Rectangle rec02 = engine->allCameras->camera02.rectForCam;
    Rectangle rec03 = engine->allCameras->camera03.rectForCam;

    engine->allCameras->camera03.rectForCam = (Rectangle){0.0f, 0.0f,
        rec03.width + diff.x, rec03.height};
    engine->allCameras->camera03.textForCam = LoadRenderTexture(engine->screenSize.x, 30);
    
    engine->allCameras->camera02.rectForCam = (Rectangle){rec02.x + diff.x / 2, rec02.y + diff.y / 2,
        rec02.width + diff.x / 2, rec02.height + diff.y / 2};
    engine->allCameras->camera02.textForCam = LoadRenderTexture(rec02.width, rec02.height);

    engine->allCameras->camera01.rectForCam = (Rectangle){rec01.x + diff.x / 2, rec01.y,
        rec01.width + diff.x / 2, rec01.height + diff.y / 2};
    engine->allCameras->camera01.textForCam = LoadRenderTexture(rec01.width, rec01.height);

    engine->allCameras->camera00.rectForCam = (Rectangle){rec00.x, rec00.y,
        rec00.width + diff.x / 2, rec00.height + diff.y};
    engine->allCameras->camera00.textForCam = LoadRenderTexture(rec00.width, rec00.height);

    // Adjust buttons menus
    button_set_position(engine->buttonsMenuUp.play, (Vector2){engine->screenSize.x /2 - 15, 2});
    button_set_position(engine->buttonsMenuUp.stop, (Vector2){engine->screenSize.x /2 + 15, 2});
}

void    adjust_right_panel_vert(Engine *engine, int x)
{
    engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height);
    engine->allCameras->camera02.rectForCam.width -= x;
    engine->allCameras->camera02.rectForCam.x += x;

    engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);
    engine->allCameras->camera01.rectForCam.width -= x;
    engine->allCameras->camera01.rectForCam.x += x;

    engine->allCameras->camera00.textForCam = LoadRenderTexture(engine->allCameras->camera00.rectForCam.width, engine->allCameras->camera00.rectForCam.height);
    engine->allCameras->camera00.rectForCam.width += x;
}

void    adjust_right_panel_hori(Engine *engine, int y)
{
    DE_INFO("Adjust Right Panel Horisontal");
    DE_INFO("Y: %d", y);
    DE_INFO("Height: %d", engine->allCameras->camera02.rectForCam.height);

    engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height);
    engine->allCameras->camera02.rectForCam.height -= y;
    engine->allCameras->camera02.rectForCam.y += y;

    engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);
    engine->allCameras->camera01.rectForCam.height += y;
    // engine->allCameras->camera01.rectForCam.y += y;
}

bl8     mouse_on_line_vert = false;
bl8     mouse_on_line_vert_ct = false;
bl8     mouse_on_line_hori = false;
bl8     mouse_on_line_hori_ct = false;
Vector2 mouse_on_line_pos = (Vector2){0, 0};
Vector2 mouse_on_line_pos_old = (Vector2){0, 0};
int line_hori_width = 4;
int line_vert_width = 4;

void    reset_resize_values(Engine *engine)
{
    mouse_on_line_vert_ct = false;
    mouse_on_line_hori_ct = false;
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    mouse_on_line_pos = (Vector2){0, 0};
    mouse_on_line_vert = false;
    mouse_on_line_hori = false;
    line_hori_width = 4;
    line_vert_width = 4;
}

void    resize_right_panel(Engine *engine)
{
    if (engine->allCameras->camera01.rectForCam.width > engine->screenSize.x - 300)
    {
        DE_INFO("Resize Right Panel Up");
        engine->allCameras->camera01.rectForCam.width = engine->screenSize.x - 301;
        engine->allCameras->camera01.rectForCam.x = engine->screenSize.x - engine->allCameras->camera01.rectForCam.width;
        engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);

        engine->allCameras->camera02.rectForCam.width = engine->screenSize.x - 301;
        engine->allCameras->camera02.rectForCam.x = engine->screenSize.x - engine->allCameras->camera02.rectForCam.width;
        engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height - 30);

        engine->allCameras->camera00.rectForCam.width = engine->screenSize.x - engine->allCameras->camera01.rectForCam.width;
        engine->allCameras->camera00.textForCam = LoadRenderTexture(engine->allCameras->camera00.rectForCam.width, engine->screenSize.y - 30);

        reset_resize_values(engine);
        return;
    }
    else if (engine->allCameras->camera01.rectForCam.width < 300)
    {
        DE_INFO("Resize Right Panel Down");
        engine->allCameras->camera01.rectForCam.width = 301;
        engine->allCameras->camera01.rectForCam.x = engine->screenSize.x - engine->allCameras->camera01.rectForCam.width;
        engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);

        engine->allCameras->camera02.rectForCam.width = 301;
        engine->allCameras->camera02.rectForCam.x = engine->screenSize.x - engine->allCameras->camera02.rectForCam.width;
        engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height - 30);

        engine->allCameras->camera00.rectForCam.width = engine->screenSize.x - engine->allCameras->camera01.rectForCam.width;
        engine->allCameras->camera00.textForCam = LoadRenderTexture(engine->allCameras->camera00.rectForCam.width, engine->screenSize.y - 30);

        reset_resize_values(engine);
        return;
    }

    if (engine->allCameras->camera02.rectForCam.height > engine->screenSize.y / 4 * 3 - 30)
    {
        DE_INFO("Resize Right Panel Down");
        engine->allCameras->camera01.rectForCam.height = engine->screenSize.y / 4;
        engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);

        engine->allCameras->camera02.rectForCam.height = engine->screenSize.y / 4 * 3 - 30;
        engine->allCameras->camera02.rectForCam.y = engine->screenSize.y / 4 + 30;
        engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height);
        reset_resize_values(engine);
    }
    else if (engine->allCameras->camera02.rectForCam.height < 200)
    {
        DE_INFO("Resize Right Panel Up");
        engine->allCameras->camera01.rectForCam.height = engine->screenSize.y / 4 * 3 -30;
        // engine->allCameras->camera01.rectForCam.y = engine->screenSize.y / 3 + 30;
        engine->allCameras->camera01.textForCam = LoadRenderTexture(engine->allCameras->camera01.rectForCam.width, engine->allCameras->camera01.rectForCam.height);

        engine->allCameras->camera02.rectForCam.height = 200;
        engine->allCameras->camera02.rectForCam.y = engine->screenSize.y / 4 * 3;
        engine->allCameras->camera02.textForCam = LoadRenderTexture(engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height);
        reset_resize_values(engine);
    }

    // DE_DEBUG("cam 2 width: %d", engine->allCameras->camera02.rectForCam.width);
    // DE_DEBUG("cam 2 height: %d", engine->allCameras->camera02.rectForCam.height);
    // DE_DEBUG("cam 2 x: %d", engine->allCameras->camera02.rectForCam.x);
    // DE_DEBUG("cam 2 y: %d", engine->allCameras->camera02.rectForCam.y);

    if (CheckCollisionPointLine(GetMousePosition(), (Vector2){engine->allCameras->camera01.rectForCam.x, engine->allCameras->camera01.rectForCam.y},
        (Vector2){engine->allCameras->camera01.rectForCam.x, engine->allCameras->camera01.rectForCam.y + engine->allCameras->camera01.rectForCam.height}, line_vert_width)
            || CheckCollisionPointLine(GetMousePosition(), (Vector2){engine->allCameras->camera02.rectForCam.x, engine->allCameras->camera02.rectForCam.y},
                (Vector2){engine->allCameras->camera02.rectForCam.x, engine->allCameras->camera02.rectForCam.y + engine->allCameras->camera02.rectForCam.height}, line_vert_width))
    {
        // DE_INFO("Mouse Hit Line");
        mouse_on_line_vert_ct = true;
        mouse_on_line_hori_ct = false;
        mouse_on_line_pos = GetMousePosition();
        SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
    }
    else if (mouse_on_line_vert_ct)
    {
        DE_INFO("Mouse not on line");
        reset_resize_values(engine);
    }

    if (CheckCollisionPointLine(GetMousePosition(), (Vector2){engine->allCameras->camera02.rectForCam.x, engine->allCameras->camera02.rectForCam.y},
        (Vector2){engine->allCameras->camera02.rectForCam.x + engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.y}, line_hori_width))
    {
        // DE_INFO("Mouse Hit Horizontal Line");
        mouse_on_line_hori_ct = true;
        mouse_on_line_vert_ct = false;
        mouse_on_line_pos = GetMousePosition();
        SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
    }
    else if (mouse_on_line_hori_ct)
    {
        DE_INFO("Mouse not on line");
        reset_resize_values(engine);
    }

    if (mouse_on_line_vert_ct)
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            // DE_INFO("Click on line");
            if (mouse_on_line_pos.x != mouse_on_line_pos_old.x)
            {
                DE_INFO("Mouse move on line");
                adjust_right_panel_vert(engine, mouse_on_line_pos.x - mouse_on_line_pos_old.x);
            }
            line_vert_width = 1000;
        }
        mouse_on_line_pos_old = mouse_on_line_pos;
    }
    else if (mouse_on_line_hori_ct)
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            DE_INFO("Click on line");
            if (mouse_on_line_pos.y != mouse_on_line_pos_old.y)
            {
                DE_INFO("Mouse move on line");
                adjust_right_panel_hori(engine, mouse_on_line_pos.y - mouse_on_line_pos_old.y);
            }
            line_hori_width = 1000;
        }
        mouse_on_line_pos_old = mouse_on_line_pos;
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        reset_resize_values(engine);
    }
}

void    window_events(Engine *engine)
{
    if (IsWindowResized()) // Resize window events
    {
        engine->lastScreenSize = engine->screenSize;
        engine->screenSize.x = GetScreenWidth();
        engine->screenSize.y = GetScreenHeight();

        adjust_menu_camera(engine);
        DE_INFO("Window resized in engine");
    }

    resize_right_panel(engine);
}

void    draw_rectangle_borders(Rectangle rectangle, Color color, int thickness)
{
    DrawLineEx((Vector2){rectangle.x, rectangle.y}, (Vector2){rectangle.x + rectangle.width, rectangle.y}, thickness, color); // Line up
    DrawLineEx((Vector2){rectangle.x + rectangle.width, rectangle.y + rectangle.height}, (Vector2){rectangle.x, rectangle.y + rectangle.height}, thickness, color); // Line down
    DrawLineEx((Vector2){rectangle.x + rectangle.width, rectangle.y}, (Vector2){rectangle.x + rectangle.width, rectangle.y + rectangle.height}, thickness, color); // Line right
    DrawLineEx((Vector2){rectangle.x, rectangle.y + rectangle.height}, (Vector2){rectangle.x, rectangle.y}, thickness, color); // Line left
}

void    draw_events(Engine *engine)
{
//--------------------------------------------------------------------------------------
// Update
//----------------------------------------------------------------------------------
    // UpdateCamera(&allCameras->camera00.camera3D, CAMERA_FREE);
    //** Drawning **//

    // Draw Workspace
    BeginTextureMode(engine->allCameras->camera00.textForCam);
        ClearBackground(LIGHTGRAY);
        BeginMode3D(engine->allCameras->camera00.camera3D);

            // ftControlMainPanel(engine, &cube01, engine->allCameras);

        EndMode3D();

    EndTextureMode();

//--------------------------------------------------------------------------------------//

    // Draw Control Panel side up
    BeginTextureMode(engine->allCameras->camera01.textForCam);
        ClearBackground(DARKGRAY);
        BeginMode2D(engine->allCameras->camera01.camera2D);

            // ftSideUpMenu2D(game);

        EndMode2D();
    EndTextureMode();

//--------------------------------------------------------------------------------------//

    // Draw Control Panel side down
    BeginTextureMode(engine->allCameras->camera02.textForCam);
        ClearBackground(DARKGRAY2);
        BeginMode2D(engine->allCameras->camera02.camera2D);

            // ftSideDownMenu3D(game);

        EndMode2D();
    EndTextureMode();

//--------------------------------------------------------------------------------------//

    // Draw Control Panel Up
    BeginTextureMode(engine->allCameras->camera03.textForCam);
        ClearBackground(DARKGRAY1);
        BeginMode2D(engine->allCameras->camera03.camera2D);

            ftUpMenu2D(engine, &engine->allCameras->camera03.camera2D);

        EndMode2D();
    EndTextureMode();

//--------------------------------------------------------------------------------------//

    // Draw render textures to the screen for all cameras
    BeginDrawing();
        ClearBackground(BLACK);
        // ImageClearBackground(&engine->allCameras->camera02.image, BLACK);
        // ImageDrawRectangle(&engine->allCameras->camera02.image, engine->allCameras->camera02.rectForCam.x, engine->allCameras->camera02.rectForCam.y, engine->allCameras->camera02.rectForCam.width, engine->allCameras->camera02.rectForCam.height, BLACK);
        Rectangle rec00 = engine->allCameras->camera00.rectForCam;
        Rectangle rec01 = engine->allCameras->camera01.rectForCam;
        Rectangle rec02 = engine->allCameras->camera02.rectForCam;
        Rectangle rec03 = engine->allCameras->camera03.rectForCam;

        DrawTextureRec(engine->allCameras->camera00.textForCam.texture, rec00, (Vector2){rec00.x, rec00.y}, WHITE);
        DrawTextureRec(engine->allCameras->camera01.textForCam.texture, rec01, (Vector2){rec01.x, rec01.y}, WHITE);
        DrawTextureRec(engine->allCameras->camera02.textForCam.texture, rec02, (Vector2){rec02.x, rec02.y}, WHITE);
        DrawTextureRec(engine->allCameras->camera03.textForCam.texture, rec03, (Vector2){rec03.x, rec03.y}, WHITE);

        // draw_rectangle_borders(rec00, PURPLE, 3);
        draw_rectangle_borders(rec01, BLUE, 3);
        draw_rectangle_borders(rec02, RED, 3);
        // draw_rectangle_borders(rec03, PURPLE, 3);

        // Rectangle test = (Rectangle){100, 100, 200, 200};
        // draw_rectangle_borders(test, RED, 3);

        ftDrawDropdownMenu(engine);
    EndDrawing();
}

void    dr_update(Engine *engine)
{
    input_events(engine);
    window_events(engine);

    // put intro screen
    if (engine->introCt)
    {
        static double startTime = 0;
        
        if (startTime == 0)
        {
            startTime = GetTime(); // Initialize time
        }
        
        draw_msg_intro();
        
        if (GetTime() - startTime >= 1.0) // Check time passed
        {
            engine->introCt = false;
            startTime = 0; // Reset for future use if needed
        }
    }
    else
    {
        draw_events(engine);
    }
}
