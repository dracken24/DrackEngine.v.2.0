#include "../includes/EngineW.hpp"
#include "../../core/srcs/memory/dmemory.h"

#include <iostream>

EngineW::EngineW() : w_isInitialized(false)
{
    // Initialisation des membres à zéro
    // memset(&coreInfos, 0, sizeof(CoreInfos));
    // memset(&w_engine, 0, sizeof(Engine));
    Init();
}

EngineW::~EngineW()
{
    if (w_isInitialized)
    {
        Shutdown();
    }
    print_memory_usage("Exit");
}

bool EngineW::Init()
{
    DE_DEBUG("w_isInitialized: %d", w_isInitialized);
    if (w_isInitialized)
    {
        return false;
    }

    initialize_memory();
    if (!dr_init(&w_engine, &coreInfos))
    {
        DE_DEBUG("Failed to initialize engine 1");
        return false;
    }

    w_isInitialized = true;
    return true;
}

void EngineW::Update()
{
    if (!w_isInitialized)
        return;
    
    dr_update(&w_engine, &coreInfos);
}

void EngineW::Shutdown()
{
    if (!w_isInitialized)
        return;

    dr_exit(&w_engine, &coreInfos);
    shutdown_memory();
    w_isInitialized = false;
}
