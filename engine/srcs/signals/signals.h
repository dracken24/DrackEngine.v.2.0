#include "../../includes/engine.h"
#include "../memory/dmemory.h"

# include <signal.h>

#define SIGNAL_CLEANUP SIGUSR1

extern Engine *g_engine;

void cleanup_handler(int signum);
