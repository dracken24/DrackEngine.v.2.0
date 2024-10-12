#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

// Main for new project window
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("argc: %d\n", argc);
        printf("Usage: %s <width> <height> <title>\n", argv[0]);
        return 1;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    const char *title = argv[3];

    InitWindow(width, height, title);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawText("New Project !", width / 2 - MeasureText("New Project !", 20) / 2, height / 2, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
