#ifndef SIGNALS_H
# define SIGNALS_H

#include "../../includes/engine.h"
#include "../memory/dmemory.h"

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

#define SIGNAL_CLEANUP SIGUSR1
#define SIGNAL_CLEANUP_OTHERS_WINDOWS SIGUSR2

extern Engine *g_engine;

void cleanup_handler(int signum);
void sigchld_handler(int signum);

#endif
