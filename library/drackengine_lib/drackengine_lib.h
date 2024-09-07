#ifndef DRACKENGINE_LIB_H
# define DRACKENGINE_LIB_H

# include "logger.h"
# include "utility/defines.h"

bl8 log_init(uint64 *memoryRequirement, void *state);
void log_shutdown(void *state);

#endif
