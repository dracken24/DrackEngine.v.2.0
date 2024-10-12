#define _XOPEN_SOURCE 700

#include "../windows_utility.h"

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>

#define SIGNAL_CLEANUP SIGUSR1

volatile bool running = true;

// Main for new project window
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("argc: %d\n", argc);
        printf("Usage: %s <width> <height> <title>\n", argv[0]);
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = cleanup_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGNAL_CLEANUP, &sa, NULL);

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    const char *title = argv[3];

    InitWindow(width, height, title);

    while (!WindowShouldClose() && running)
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawText("New Project !", width / 2 - MeasureText("New Project !", 20) / 2, height / 2, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
