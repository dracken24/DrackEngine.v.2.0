#ifndef WINDOW07_H
# define WINDOW07_H

#ifdef __cplusplus
extern "C" {
#endif

# include "../../../../includes/Config/menus.h"
# include "../../../utility/text_entry.h"

extern Engine *g_engine;

# define CAM07_BORDER_TICK 8
# define CAM07_BORDER_COLOR VERRYDARKGRAY
# define CAM07_MAIN_TEXT_COLOR DARKPURPLE2
# define CAM07_CLEAR_BACKGROUND GRAYPURPLE
# define CAM07_SPACING 1
# define CAM07_DEFAULT_FONT g_engine->fonts.defaultFont
# define CAM07_FONT_ADJUST -5

// Files dropdown menu
extern FilesNew     g_files_new;
extern FilesOpen    g_files_open;
extern FilesSave    g_files_save;
extern FilesSaveAs  g_files_save_as;
extern FilesExport  g_files_export;

// Settings dropdown menu
extern SettingsEngine   g_settings_engine;
extern SettingsProject  g_settings_project;
extern SettingsOptions  g_settings_options;

// Help dropdown menu
extern HelpSupport  g_help_support;
extern HelpDoc      g_help_doc;

extern bl8 window_in_operation;
extern bl8 refresh_frame;

//##############################################################################//
//###                     ### Functions Definitions ###                      ###//
//##############################################################################//
//******************************************************************************//
//***                           menu_fonction.c                              ***//
//******************************************************************************//

void    keys_events(Engine *engine);

//******************************************************************************//
//***                               update.c                                 ***//
//******************************************************************************//

void	mount_all_cameras_engine(Engine *engine);
void	draw_cameras_textures(Engine *engine);

//******************************************************************************//
//***                             new_project.c                              ***//
//******************************************************************************//

void    new_project_init(CoreInfos const *coreInfos);
void    new_project_update(CoreInfos const *coreInfos);
void    new_project_clean(void);
void    new_project_destroy(void);

//******************************************************************************//
//***                             open_project.c                             ***//
//******************************************************************************//

void    open_project_init(void);
void    open_project_update(void);
void    open_project_clean(void);
void    open_project_destroy(void);

//******************************************************************************//
//***                             save_project.c                             ***//
//******************************************************************************//

void    save_project_init(void);
void    save_project_update(void);
void    save_project_clean(void);
void    save_project_destroy(void);

//******************************************************************************//
//***                            save_as_project.c                           ***//
//******************************************************************************//

void    save_as_project_init(void);
void    save_as_project_update(void);
void    save_as_project_clean(void);
void    save_as_project_destroy(void);

//******************************************************************************//
//***                            export_project.c                            ***//
//******************************************************************************//

void    export_project_init(void);
void    export_project_update(void);
void    export_project_clean(void);
void    export_project_destroy(void);

//******************************************************************************//
//***                            settings_engine.c                           ***//
//******************************************************************************//

void    settings_engine_init(void);
void    settings_engine_update(void);
void    settings_engine_clean(void);
void    settings_engine_destroy(void);

//******************************************************************************//
//***                           settings_project.c                           ***//
//******************************************************************************//

void    settings_project_init(void);
void    settings_project_update(void);
void    settings_project_clean(void);
void    settings_project_destroy(void);

//******************************************************************************//
//***                           settings_options.c                           ***//
//******************************************************************************//

void    settings_options_init(void);
void    settings_options_update(void);
void    settings_options_clean(void);
void    settings_options_destroy(void);

//******************************************************************************//
//***                              help_about.c                              ***//
//******************************************************************************//

void    help_about_init(void);
void    help_about_update(void);
void    help_about_clean(void);
void    help_about_destroy(void);

//******************************************************************************//
//***                             help_support.c                             ***//
//******************************************************************************//

void    help_support_init(void);
void    help_support_update(void);
void    help_support_clean(void);
void    help_support_destroy(void);

//******************************************************************************//
//***                             help_support.c                             ***//
//******************************************************************************//

void    help_doc_init(void);
void    help_doc_update(void);
void    help_doc_clean(void);
void    help_doc_destroy(void);

#ifdef __cplusplus
}
#endif

#endif