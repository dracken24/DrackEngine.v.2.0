# define SIGNAL_CLEANUP SIGUSR1

# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>

# include "../library/drackengine_lib/drackengine_lib.h"
extern volatile bool running;

void    cleanup_handler(int signum);
