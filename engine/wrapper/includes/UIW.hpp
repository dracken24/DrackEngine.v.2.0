#ifndef UIW_HPP
# define UIW_HPP

#include "../../core/includes/engine.h"

class UI {
public:
    static void renderPanels(Engine* coreInfos);
    static void renderMenus(Engine* coreInfos);
    static void handleUIEvents(Engine* coreInfos);
};

#endif
