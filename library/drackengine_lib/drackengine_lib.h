#ifndef DRACKENGINE_LIB_H
# define DRACKENGINE_LIB_H

# include "logger.h"
# include "utility/defines.h"

DE_API bool log_init(uint64 *memoryRequirement, void *state);
DE_API void log_shutdown(void *state);

#endif
