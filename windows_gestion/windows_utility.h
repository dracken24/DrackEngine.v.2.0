# define SIGNAL_CLEANUP SIGUSR1

# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>

extern volatile bool running;

void    cleanup_handler(int signum);
