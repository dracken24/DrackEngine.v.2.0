/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    24-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:        workspace.cpp            *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "../../../core/includes/engine.h"
#include "DragDropDetect.hpp"

#include "workspace.h"

#include "raylib.h"

#include <vector>

using namespace DrackEngine::Workspace;

void update_camera(Camera3D *camera)
{
    bool is_mmb_down = IsMouseButtonDown(2);
    bool is_shift_down = IsKeyDown(KEY_LEFT_SHIFT);
    Vector2 mouse_delta = GetMouseDelta();

    if (is_mmb_down && is_shift_down)
	{
        CameraMoveRight(camera, -CAMERA_MOVE_SPEED * mouse_delta.x, true);

        Vector3 right = GetCameraRight(camera);
        Vector3 up = Vector3CrossProduct(Vector3Subtract(camera->position, camera->target), right);

        up = Vector3Scale(Vector3Normalize(up), CAMERA_MOVE_SPEED * mouse_delta.y);
        camera->position = Vector3Add(camera->position, up);
        camera->target = Vector3Add(camera->target, up);
    }
	else if (is_mmb_down)
	{
        CameraYaw(camera, -CAMERA_ROT_SPEED * mouse_delta.x, true);
        CameraPitch(camera, CAMERA_ROT_SPEED * mouse_delta.y, true, true, false);
    }

    CameraMoveToTarget(camera, -GetMouseWheelMove() * CAMERA_ZOOM_SPEED);
	// comment
}

// Draw a grid centered at (0, 0, 0)
void	draw_grid(int slices, float spacing, float thickness, Color color)
{
    int halfSlices = (int)(slices / 2);

	rlSetLineWidth(thickness);
    rlBegin(RL_LINES);
    rlColor4ub(color.r, color.g, color.b, color.a);


    for (int i = -halfSlices; i <= halfSlices; i++)
    {
        rlVertex3f((float)i*spacing, 0.0f, (float)-halfSlices*spacing);
        rlVertex3f((float)i*spacing, 0.0f, (float)halfSlices*spacing);

        rlVertex3f((float)-halfSlices*spacing, 0.0f, (float)i*spacing);
        rlVertex3f((float)halfSlices*spacing, 0.0f, (float)i*spacing);
    }
    rlEnd();
}

bl8	g_reset_workspace = false;
void    change_language(Engine *engine, const char *language);
#define ORANGE_SELECT     CLITERAL(Color){ 255, 185, 61, 255 }

void    control_main_panel(Engine *engine, DragDropDetect *dragDropDetect, Camera *camera)
{
    if (engine->allStates.currentStateMouse == MOUSE_STATE_ON_WORKSPACE || g_reset_workspace)
    {
        SceneObject* selectedObj = dragDropDetect->GetSelectedObject();
        if (selectedObj && selectedObj->model)
        {
            Vector3 position = {
                selectedObj->model->transform.m12,
                selectedObj->model->transform.m13,
                selectedObj->model->transform.m14
            };
            
            // Update the gizmo before checking clicks
            rgizmo_update(&dragDropDetect->GetGizmo(), *camera, position);
            
            // If the gizmo is in use or has been clicked
            if (dragDropDetect->IsGizmoInUse() || dragDropDetect->GetGizmo().state != RGIZMO_STATE_COLD)
            {
                selectedObj->model->transform = MatrixMultiply(
                    selectedObj->model->transform, 
                    rgizmo_get_tranform(dragDropDetect->GetGizmo(), position)
                );
            }
            // Otherwise, check for clicks on objects
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                auto hits = dragDropDetect->CheckUnderTheMouse(camera);
                if (!hits.empty())
                {
                    dragDropDetect->SetSelectedObject(hits[0].objectName);
                    DE_DEBUG("object hit: %s", hits[0].objectName.c_str());
                }
                else
                {
                    dragDropDetect->ClearSelection();
                }
            }
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            auto hits = dragDropDetect->CheckUnderTheMouse(camera);
            if (!hits.empty())
            {
                dragDropDetect->SetSelectedObject(hits[0].objectName);
                DE_DEBUG("object hit: %s", hits[0].objectName.c_str());
            }
        }
    }

    ClearBackground(DARKGRAY);

    BeginMode3D(*camera);
    {
        // Draw the grid
        draw_grid(100.0, 1.0, 1.0, GRAY);

        // Draw all objects in the scene
        for (const auto& obj : dragDropDetect->GetSceneObjects())
        {
            if (obj.model)
            {
                // Draw the model
                DrawModel(*obj.model, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, PURPLE);
                
                // null pointer check
                Color wireColor = BLUE;  // Default color
                SceneObject* selectedObj = dragDropDetect->GetSelectedObject();
                if (selectedObj != nullptr && obj.name == selectedObj->name)
                {
                    wireColor = ORANGE_SELECT;
                }

				DrawModelWiresEx(*obj.model, 
					(Vector3){0.0f, 0.0f, 0.0f},
					(Vector3){0.0f, 0.0f, 0.0f},
					0.0f,
					(Vector3){1.0f, 1.0f, 1.0f},
					wireColor);
            }
        }

        // Draw the X, Y, Z axes
        DrawLine3D(
            (Vector3){-50.0f, 0.0f, 0.0f},
            (Vector3){50.0f, 0.0f, 0.0f},
            (Color){ 230, 41, 55, 124 } // RED - X axis
        );
        DrawLine3D(
            (Vector3){0.0f, -50.0f, 0.0f},
            (Vector3){0.0f, 50.0f, 0.0f},
            (Color){ 0, 228, 48, 124 } // GREEN - Y axis
        );
        DrawLine3D(
            (Vector3){0.0f, 0.0f, -50.0f},
            (Vector3){0.0f, 0.0f, 50.0f},
            (Color){ 0, 82, 172, 124 } // DARKBLUE - Z axis
        );

        // Draw the gizmo if an object is selected
        SceneObject* selectedObj = dragDropDetect->GetSelectedObject();
        if (selectedObj && selectedObj->model)
        {
            Vector3 position = {
                selectedObj->model->transform.m12,
                selectedObj->model->transform.m13,
                selectedObj->model->transform.m14
            };
            rgizmo_draw(dragDropDetect->GetGizmo(), *camera, position);
        }
    }
    EndMode3D();
}
