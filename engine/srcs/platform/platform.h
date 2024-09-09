#ifndef PLATFORM_H
# define PLATFORM_H

# include "../includes/engine_defines.h"

typedef struct platform_state
{
    void* internal_state;
} platform_state;

bl8 platform_startup(
    platform_state* plat_state,
    const char* application_name,
    sint32 x,
    sint32 y,
    sint32 width,
    sint32 height);

void platform_shutdown(platform_state* plat_state);

bl8 platform_pump_messages(platform_state* plat_state);

void* platform_allocate(uint64 size, bl8 aligned);
void platform_free(void* block, bl8 aligned);
void* platform_zero_memory(void* block, uint64 size);
void* platform_copy_memory(void* dest, const void* source, uint64 size);
void* platform_set_memory(void* dest, sint32 value, uint64 size);

void platform_console_write(const char* message, uint8 colour);
void platform_console_write_error(const char* message, uint8 colour);

dbl64 platform_get_absolute_time();

// Sleep on the thread for the provided ms. This blocks the main thread.
// Should only be used for giving time back to the OS for unused update power.
// Therefore it is not exported.
void platform_sleep(uint64 ms);

#endif // PLATFORM_H
