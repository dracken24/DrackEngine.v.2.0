#pragma once

#include "../../core/includes/engine.h"

namespace DrackEngine
{
    class UI
    {
        public:
            static void renderPanels(Engine* coreInfos);
            static void renderMenus(Engine* coreInfos);
            static void handleUIEvents(Engine* coreInfos);
    };
}
