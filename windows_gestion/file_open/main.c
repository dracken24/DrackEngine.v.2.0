#define _XOPEN_SOURCE 700

// #include "../windows_utility.h"

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>

#include "../../library/drackengine_lib/drackengine_lib.h"

#define SIGNAL_CLEANUP_OTHERS_WINDOWS SIGUSR2

volatile sig_atomic_t running = 1;

void cleanup_handler(int signum)
{
    DE_ERROR("Reçu signal dans windows_utility #: %d", signum);
    if (signum == SIGNAL_CLEANUP_OTHERS_WINDOWS)
    {
        DE_ERROR("SIGNAL_CLEANUP_OTHERS_WINDOWS dans windows_utility signal %d", signum);
        running = false;
    }
}

// Main for new project window
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("argc: %d\n", argc);
        printf("Usage: %s <width> <height> <title>\n", argv[0]);
        return 1;
    }

    DE_INFO("Processus enfant démarré avec PID: %d", getpid());

    struct sigaction sa;
    sa.sa_handler = cleanup_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGNAL_CLEANUP_OTHERS_WINDOWS, &sa, NULL) == -1)
    {
        DE_ERROR("Erreur lors de la configuration du gestionnaire de signal");
        perror("sigaction");
        return 1;
    }
    DE_INFO("Gestionnaire de signal configuré pour SIGNAL_CLEANUP_OTHERS_WINDOWS");

    // Débloquer le signal
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGNAL_CLEANUP_OTHERS_WINDOWS);
    if (sigprocmask(SIG_UNBLOCK, &set, NULL) == -1)
    {
        DE_ERROR("Erreur lors du déblocage du signal");
        perror("sigprocmask");
        return 1;
    }
    DE_INFO("Signal SIGNAL_CLEANUP_OTHERS_WINDOWS débloqué");

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    const char *title = argv[3];

    InitWindow(width, height, title);

    while (!WindowShouldClose() && running)
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawText("Open Project !", width / 2 - MeasureText("Open Project !", 20) / 2, height / 2, 20, LIGHTGRAY);
        EndDrawing();
        if (running == false)
        {
            DE_INFO("Signal reçu, sortie de la boucle");
        }
    }
    DE_INFO("Open Project window closed successfully");

    CloseWindow();

    return 0;
}
