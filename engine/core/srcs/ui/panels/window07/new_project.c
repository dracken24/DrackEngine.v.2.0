/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	      27-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 new_project.c          *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "window07.h"
#include "file_dialog.h"
#include "../../../memory/dmemory.h"
#include "../../../errors_manager/popUp/error_to_popUp.h"

#include <cjson/cJSON.h>

void	create_structure_projet(const char *cheminBase, const char *jsonString, BuildProject project);
FILE	*open_file(char const *fileName, const char *mode);
char	*file_to_string(FILE *file);
bl8		write_json_to_file(const char *filePath, cJSON *jsonObject);

FilesNew g_files_new;

// --------------------------------------------------------------------------------


void	build_new_project(BuildProject project)
{
	char const	path[] = "../engine/srcs/save_system/config_files/structure_projet.json";
    FILE *file = open_file(path, "r");
	// fopen("../engine/srcs/save_system/config_files/structure_projet.json", "r");
    if (file == NULL)
    {
		DE_WARNING("Null file path open with path: %s", path);
        return;
    }

    char *jsonString = file_to_string(file);

    // Create the project structure
    create_structure_projet(project.fileNew.pathEntry.text, jsonString, project);
    
    de_free(jsonString, sizeof(char) * ftell(file) + 1, MEMORY_TAG_STRING);
	fclose(file);
}

// Fn pointer button change path
static FileDialog g_fileDialog;
static bl8	delayCt = false;
static CoreInfos core_infos;
// static bl8	popUpInUse = false;
static int msgNumber = -1;

void	update_popUp(void)
{
	bl8	*popUpInUse = &g_engine->errorManager.errorToPopUp.popUpInUse;

	if (delayCt == true)
	{
		*popUpInUse = true;
		delayCt = false;
	}
	else if (*popUpInUse == true)
	{
		if (msgNumber >= 0)
		{
			switch (msgNumber)
			{
			case 0:
				draw_popUp(g_engine->errorManager.errorToPopUp, false, "*** Need A Project Name ***");
				break;
			case 1:
				draw_popUp(g_engine->errorManager.errorToPopUp, false, "*** Need A Version Number ***");
				break;
			case 2:
				draw_popUp(g_engine->errorManager.errorToPopUp, false, "*** Need A Valid Path ***");
				break;
			case 3:
				draw_popUp(g_engine->errorManager.errorToPopUp, false, "*** Project name exist ***");
				break;
			}
		}

		Rectangle cam07Rect = get_camera07_rect();
		Rectangle collisionRec = g_engine->errorManager.errorToPopUp.rect;
		collisionRec.x += cam07Rect.x;
		collisionRec.y += cam07Rect.y;
		if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(GetMousePosition(), collisionRec))
			|| IsKeyPressed(KEY_ESCAPE))
		{
			change_view(g_engine, STATE_VIEW_FILES_NEW_PROJECT, true, NULL, NULL);
			*popUpInUse = false;
			msgNumber = -1;
		}
	}
}

bl8	check_new_Project_entry(FilesNew *projectVars)
{
	// DE_WARNING("*** valid path name ***: %s", projectVars->pathEntry.text);
	// DE_WARNING("*** valid path ***: %d", DirectoryExists(projectVars->pathEntry.text));
	// Check if project have a name
	if (!projectVars->projectNameEntry.text || ft_strlen(projectVars->projectNameEntry.text) <= 0)
	{
		DE_WARNING("*** Need A Project Name ***");
		change_view(g_engine, STATE_VIEW_SUB_WINDOW, true, NULL, NULL);
		delayCt = true;
		msgNumber = 0;
		// init_ErrorToPopUp(&g_engine->errorManager.errorToPopUp, REC_ERR_TO_POPUP_DEFAULT_CAM07, 2, GRAY);

		return false;
	}
	// Check if project have a version
	if (!projectVars->versionEntry.text || ft_strlen(projectVars->versionEntry.text) <= 0)
	{
		DE_WARNING("*** Need A Project Vertion ***");
		// init_ErrorToPopUp(&g_engine->errorManager.errorToPopUp, REC_ERR_TO_POPUP_DEFAULT_CAM07, 2, GRAY);
		change_view(g_engine, STATE_VIEW_SUB_WINDOW, true, NULL, NULL);
		delayCt = true;
		msgNumber = 1;

		return false;
	}
	// Check if project have a valid path
	if (!DirectoryExists(projectVars->pathEntry.text))
	{
		DE_WARNING("*** Need A Valid Path ***");
		// init_ErrorToPopUp(&g_engine->errorManager.errorToPopUp, REC_ERR_TO_POPUP_DEFAULT_CAM07, 2, GRAY);
		change_view(g_engine, STATE_VIEW_SUB_WINDOW, true, NULL, NULL);
		delayCt = true;
		msgNumber = 2;

		return false;
	}
	FilePathList allPath = LoadDirectoryFiles(projectVars->pathEntry.text);
	DE_DEBUG("capacity: %d", allPath.capacity);
	DE_DEBUG("count: %d", allPath.count);

#ifdef DE_PLATFORM_LINUX
	// Check if file existe Linux style
	for (int i = 0; i < allPath.count; i++)
	{
		// DE_WARNING("PTR len: %s", allPath.paths[i]);
		char **splitName = ft_split(allPath.paths[i], '/');
		int len = ft_nbr_ptr(splitName) - 2;
		
		// DE_WARNING("File Name: %s", splitName[len]);
		if (ft_strncmp(splitName[len], projectVars->projectNameEntry.text, ft_strlen(splitName[len])) == 0)
		{
			DE_WARNING("Project Exist");
			change_view(g_engine, STATE_VIEW_SUB_WINDOW, true, NULL, NULL);
			msgNumber = 3;
			delayCt = true;
			ft_free_ptr((void **)splitName);
			return false;
		}
		ft_free_ptr((void **)splitName);
	}
#endif

	return true;
}

// Fn pointer fo button create project
void	create_new_project(void *userData)
{
	FilesNew *projectVars = (FilesNew *)userData;

	DE_DEBUG("Name: %s", projectVars->projectNameEntry.text);

	if (check_new_Project_entry(projectVars) == false)
	{
		return;
	}
	

	DE_DEBUG("create_new_project Validate: %s", projectVars->projectNameEntry.text);
	BuildProject project;
	project.fileNew = *projectVars;
	build_new_project(project);

	// Mount path for write in projectSettings.json
	char *filePath = malloc(sizeof(char));
	filePath[0] = '\0';
	filePath = ft_strjoin(filePath, projectVars->pathEntry.text, 1);
	filePath = ft_strjoin(filePath, "/", 1);
	filePath = ft_strjoin(filePath, projectVars->projectNameEntry.text, 1);
	filePath = ft_strjoin(filePath, "/Engine System/ProjectSettings.json", 1);

	// DE_DEBUG("Path for settings json: %s", filePath);

	// Create json object
	{
		cJSON *jsonObj = cJSON_CreateObject();

		// Add project informations
		cJSON_AddStringToObject(jsonObj, "projectName", projectVars->projectNameEntry.text);
		cJSON_AddStringToObject(jsonObj, "projectVersion", projectVars->versionEntry.text);
		cJSON_AddStringToObject(jsonObj, "path", projectVars->pathEntry.text);

		// Add config informations
		cJSON *configObj = cJSON_CreateObject();
		cJSON_AddStringToObject(configObj, "engineVersion", core_infos.coreVersion);
		cJSON_AddBoolToObject(configObj, "debugMode", true);
		cJSON_AddNumberToObject(configObj, "targetFPS", g_engine->userSettings.currentFPS);
		cJSON_AddItemToObject(jsonObj, "config", configObj);

		// Write to file
		write_json_to_file(filePath, jsonObj);

		cJSON_Delete(jsonObj);
	}
	free(filePath);

	g_engine->inputEventCt = true;
}

void	update_new_project(void)
{
    // DE_DEBUG("Debug 1");
	// DE_DEBUG("Debug 1: %d", sizeof(int));
	// DE_DEBUG("Debug 1: %d", sizeof(float));
	// DE_DEBUG("Debug 1: %d", sizeof(double));
	if (g_fileDialog.isOpen)
    {
		Vector2 camPos = (Vector2){g_engine->allCameras->camera07.rectForCam.x, g_engine->allCameras->camera07.rectForCam.y};
        draw_file_dialog(&g_fileDialog, camPos);
        
        if (file_dialog_should_close(&g_fileDialog))
        {
            if (strlen(g_fileDialog.selectedPath) > 0)
            {
                // Update Path Entry
                strncpy(g_files_new.pathEntry.text, g_fileDialog.selectedPath, 
                        g_files_new.pathEntry.maxLength);
                g_files_new.pathEntry.textSize = strlen(g_fileDialog.selectedPath);
                g_files_new.pathEntry.cursorPosition = g_files_new.pathEntry.textSize;
            }
            g_fileDialog.isOpen = false;
        }
		if (IsKeyPressed(KEY_ESCAPE) || file_dialog_should_close(&g_fileDialog))
		{
			// DE_DEBUG("Debug 3");
			g_fileDialog.shouldClose = true;
			g_engine->allStates.lastStateView = g_engine->allStates.currentStateView;
    		g_engine->allStates.currentStateView = STATE_VIEW_FILES_NEW_PROJECT;
		}
        return; // Stop the rest of the update when the dialog is open
    }
}

void change_path(void *userData)
{
	DE_DEBUG("Button change_path Clicked: %s", userData);
    TextBox* pathEntry = (TextBox*)userData;
    init_file_dialog(&g_fileDialog, pathEntry->text, g_engine->allCameras->camera07.rectForCam);
	g_fileDialog.isOpen = true;
	change_view(g_engine, STATE_VIEW_SUB_WINDOW, true, NULL, NULL);
}


// --------------------------------------------------------------------------------

void	init_textboxes(void)
{
	ft_strlcpy(g_files_new.versionEntry.text, "v1.0.0.0", 9);
	g_files_new.versionEntry.textSize = 8;
	// DE_DEBUG("versionEntry: %s", g_files_new.versionEntry.text);
}

void    new_project_init(CoreInfos const *coreInfos)
{
	core_infos = *coreInfos;
	// Entry Types
    Rectangle rect = { 20, 62, 300, 22};
	g_files_new.projectNameEntry = create_textBox(rect, 64);

	rect.y += 52;
	g_files_new.versionEntry = create_textBox(rect, 32);

	rect.y += 52;
	rect.width *= 2;
	g_files_new.pathEntry = create_textBox(rect, 512);

	char* default_path = (char *)GetWorkingDirectory();
	default_path = (char *)GetDirectoryPath(default_path);
	default_path = strcat(default_path, "/projects");

	ft_strlcpy(g_files_new.pathEntry.text, default_path, g_files_new.pathEntry.maxLength);

	// DE_DEBUG("Default Path: %s", default_path);

	g_files_new.pathEntry.textSize = strlen(default_path);
	g_files_new.pathEntry.cursorPosition = g_files_new.pathEntry.textSize;

	// Button Start Project
	rect = g_engine->allCameras->camera07.rectForCam;
	Vector2 size = (Vector2){180, 50};
	Vector2 pos = (Vector2){rect.width / 2  - size.x / 2, rect.height - size.y - 40};
	g_files_new.confirmButton = button_init(pos, size, DARKGRAY, DARKPURPLE2, NULL, "Create Project", 1, 0);
	button_set_bg_hover_color(&g_files_new.confirmButton, GRAY);
	button_set_bg_click_color(&g_files_new.confirmButton, LIGHTGRAY);
	button_set_font(&g_files_new.confirmButton, g_engine->fonts.defaultFont);
	button_set_function(&g_files_new.confirmButton ,*create_new_project, &g_files_new);
	// Button Change Path
	rect = g_files_new.pathEntry.rect;
	size = (Vector2){140, 35};
	pos = (Vector2){rect.x + rect.width + 20, rect.y - 14};
	g_files_new.changePathButton = button_init(pos, size, DARKGRAY, DARKPURPLE2, NULL, "Change Path", 1, 0);
	button_set_bg_hover_color(&g_files_new.changePathButton, GRAY);
	button_set_bg_click_color(&g_files_new.changePathButton, LIGHTGRAY);
	button_set_font(&g_files_new.changePathButton, g_engine->fonts.defaultFont);
	button_set_function(&g_files_new.changePathButton ,*change_path, &g_files_new.pathEntry);

	init_textboxes();
	init_ErrorToPopUp(&g_engine->errorManager.errorToPopUp, REC_ERR_TO_POPUP_DEFAULT_CAM07, 2, GRAY);
}

void    new_project_update(CoreInfos const *coreInfos)
{
    Vector2 mpos = GetMousePosition();
	NeedBy3DCam camera_07 = g_engine->allCameras->camera07;
	Rectangle rect07 = camera_07.rectForCam;

	// WARNING: For Debug
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		// DE_WARNING("Mouse pos x: %f y: %f", mpos.x, mpos.y);
		// DE_WARNING("Text Name %s", g_files_new.projectNameEntry.text);
		// DE_WARNING("Text Name %s", g_files_new.versionEntry.text);
	}

	if (window_in_operation == false)
	{
		new_project_init(coreInfos);
		window_in_operation = true;
	}

	keys_events(g_engine);

	Rectangle adjust = {rect07.x, rect07.y, 0, 0};
	// DE_DEBUG("popUpInUse: %d", g_engine->errorManager.errorToPopUp.popUpInUse);

	// Update TextBox
	bl8 popUpInUse = g_engine->errorManager.errorToPopUp.popUpInUse;
	if (popUpInUse == false && g_fileDialog.isOpen == false)
	{
		update_textBox(&g_files_new.projectNameEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);
		update_textBox(&g_files_new.versionEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);
		update_textBox(&g_files_new.pathEntry, adjust, CAM07_DEFAULT_FONT, CAM07_SPACING, (intptr_t)NULL);
	}

	// Update all cameras
	mount_all_cameras_engine(g_engine);
	draw_cameras_textures(g_engine);

	// Mount current texture camera 07
	BeginTextureMode(g_engine->allCameras->camera07.textForCam);
		ClearBackground(CAM07_CLEAR_BACKGROUND);
		BeginMode2D(g_engine->allCameras->camera07.camera2D);

			DrawTextEx(CAM07_DEFAULT_FONT, "New Project", (Vector2){rect07.width / 2 - MeasureText("New Project", 30 + CAM07_FONT_ADJUST) / 2, 20}, 30, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);

			// Draw and catch Project Name
			DrawTextEx(CAM07_DEFAULT_FONT, "Project Name", (Vector2){20, 40}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_files_new.projectNameEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);
			// Draw and catch Project Version
			DrawTextEx(CAM07_DEFAULT_FONT, "Project Version", (Vector2){20, 92}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_files_new.versionEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);
			// Draw and catch Project Path
			DrawTextEx(CAM07_DEFAULT_FONT, "Saving Path", (Vector2){20, 144}, CAM07_DEFAULT_FONT.baseSize, CAM07_SPACING, CAM07_MAIN_TEXT_COLOR);
			draw_textBox(g_files_new.pathEntry, CAM07_DEFAULT_FONT, VERRYDARKGRAY, CAM07_SPACING, (intptr_t)NULL);
			// Draw Change Path Button
			draw_button(&g_files_new.changePathButton, (intptr_t)NULL, 1, 2, CAM07_BORDER_COLOR, (Vector2){rect07.x, rect07.y}, popUpInUse);
			
			// Draw Confirm Button
			draw_button(&g_files_new.confirmButton, (intptr_t)NULL, 1, 2, CAM07_BORDER_COLOR, (Vector2){rect07.x, rect07.y}, popUpInUse);

			update_new_project();
			update_popUp();

		EndMode2D();
	EndTextureMode();

	// Draw camera 07 texture
	BeginDrawing();

		draw_rectangle_borders(rect07, CAM07_BORDER_COLOR, CAM07_BORDER_TICK);
		DrawTextureRec(camera_07.textForCam.texture,
					(Rectangle){0, 0, camera_07.rectForCam.width, -camera_07.rectForCam.height},
					(Vector2){rect07.x, rect07.y},
					WHITE);

	EndDrawing();
}

void    new_project_clean(void)
{
    g_files_new.projectNameEntry.text[0] = '\0';
	g_files_new.projectNameEntry.textSize = 0;
}

void    new_project_destroy(void)
{
	DE_DEBUG("Unload for new_project");
    destroy_textBox(&g_files_new.projectNameEntry);
	destroy_textBox(&g_files_new.versionEntry);
	destroy_textBox(&g_files_new.pathEntry);
	button_unload(&g_files_new.confirmButton);
	button_unload(&g_files_new.changePathButton);
}
