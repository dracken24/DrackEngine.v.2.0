#include "../../../includes/engine.h"

// void    fork_for_new_window(d_Pid *pid_struct, int enum_link, const char *title)
// {
//     pid_struct->engine_pid = fork();
//     if (pid_struct->engine_pid == 0)
//     {
//         // Processus enfant
//         if (chdir("../windows_gestion/new_project") == -1) {
//             DE_ERROR("Erreur lors du changement de répertoire");
//             exit(EXIT_FAILURE);
//         }
//         pid_struct->engine_running = true;
//         execl("./new_project", "new_project", "1000", "650", "New Project", NULL);
//         DE_ERROR("Erreur lors du lancement de new_project");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid_struct->engine_pid < 0)
//     {
//         // Erreur lors du fork
//         perror("Erreur lors du fork");
//     }
//     else
//     {
//         // Processus parent
//         pid_struct->enum_link = enum_link;
//         pid_struct->engine_running = true;
//         DE_INFO("Processus enfant créé avec PID: %d", pid_struct->engine_pid);
//     }
// }

// void    fork_for_file_open(d_Pid *pid_struct, int enum_link, const char *title)
// {
//     pid_struct->engine_pid = fork();
//     if (pid_struct->engine_pid == 0)
//     {
//         // Processus enfant
//         if (chdir("../windows_gestion/file_open") == -1) {
//             DE_ERROR("Erreur lors du changement de répertoire");
//             exit(EXIT_FAILURE);
//         }
//         pid_struct->engine_running = true;
//         execl("./file_open", "file_open", "1000", "650", "Open Project", NULL);
//         DE_ERROR("Erreur lors du lancement de file_open");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid_struct->engine_pid < 0)
//     {
//         // Erreur lors du fork
//         perror("Erreur lors du fork");
//     }
//     else
//     {
//         // Processus parent
//         pid_struct->enum_link = enum_link;
//         pid_struct->engine_running = true;
//         DE_INFO("Processus enfant créé avec PID: %d", pid_struct->engine_pid);
//     }
// }
