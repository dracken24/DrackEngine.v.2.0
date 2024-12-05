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
	// Model *model = &engine->testWorkspace.model;
	// Model *modelCube = &engine->testWorkspace.modelCube;
	// RGizmo *gizmo = &engine->gizmo;
	// Vector3 position = { model->transform.m12, model->transform.m13, model->transform.m14 };

		// DE_DEBUG("REACH");
		// DE_DEBUG("MOUSE_STATE_ON_WORKSPACE: %d", engine->allStates.currentStateMouse);
	if (engine->allStates.currentStateMouse == MOUSE_STATE_ON_WORKSPACE || g_reset_workspace)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			auto hits = dragDropDetect->CheckUnderTheMouse(camera);
			if (!hits.empty())
			{
				std::string objectName = hits[0].sceneObject.name;  // Nom du premier objet touché
			}

			// // Iterate through all collisions
			// for (const auto& hit : hits)
			// {
			// 	DE_INFO("*********************************************************");
			// 	switch (hit.type)
			// 	{
			// 		case CollisionInfo::MODEL:
			// 			DE_DEBUG("Hit MODEL1");
			// 			break;
			// 		case CollisionInfo::CUBE:
			// 			DE_DEBUG("Hit CUBE");
			// 			break;
			// 		case CollisionInfo::PLANE:
			// 			DE_DEBUG("Hit PLANE");
			// 			break;
			// 		default:
			// 			break;
			// 	}
				
			// 	// Access collision information
			// 	Vector3 hitPoint = hit.collision.point;    // Impact point
			// 	Vector3 normal = hit.collision.normal;     // Surface normal
			// 	float distance = hit.collision.distance;   // Distance from ray origin

			// 	DE_DEBUG("distance : %f", distance);
			// 	DE_DEBUG("normal   : %f, %f, %f", normal.x, normal.y, normal.z);
			// 	DE_DEBUG("hitPoint : %f, %f, %f", hitPoint.x, hitPoint.y, hitPoint.z);
				DE_INFO("*********************************************************");
			// }
		}
		// DE_DEBUG("g_reset_workspace: %d", g_reset_workspace);
		//NOTE: attach Guizmo to an object 
		// if (IsKeyDown(KEY_H))
		// {
		// 	position = (Vector3){ modelCube->transform.m12, modelCube->transform.m13, modelCube->transform.m14};
		// 	rgizmo_update(gizmo, *camera, position);
		// 	modelCube->transform = MatrixMultiply(modelCube->transform, rgizmo_get_tranform(*gizmo, position));
		// }
		// else
		// {
		// 	// position = (Vector3){ model->transform.m12, model->transform.m13, model->transform.m14};
		// 	rgizmo_update(gizmo, *camera, position);
		// 	model->transform = MatrixMultiply(model->transform, rgizmo_get_tranform(*gizmo, position));
		// }

		// NOTE: Release Gizmo when leave workspace
		// if (g_reset_workspace)
		// {
		// 	g_reset_workspace = false;
		// 	if (gizmo->state > 5)
		// 	{
		// 		gizmo->state = RGIZMO_STATE_COLD;
		// 	}
		// }
	}
	// DE_DEBUG("gizmo->state: %d", gizmo->state);

	ClearBackground(DARKGRAY);
	// rlEnableDepthTest();

	BeginMode3D(*camera);
	{
		draw_grid(100.0, 1.0, 1.0, GRAY);

		// DrawModel(*model, (Vector3){0.0, 0.0, 0.0}, 1.0, PURPLE);
		// DrawModelWiresEx(*model, (Vector3){0.0, 0.0, 0.0}, (Vector3){0.0, 0.0, 0.0}, 0.0, (Vector3){1.0, 1.0, 1.0}, BLUE);
		// DrawModel(*modelCube, (Vector3){0.0, 0.0, 0.0}, 1.0, PURPLE);
		// DrawModelWiresEx(*modelCube, (Vector3){0.0, 0.0, 0.0}, (Vector3){0.0, 0.0, 0.0}, 0.0, (Vector3){1.0, 1.0, 1.0}, BLUE);
		
		// rlSetLineWidth(2);
		// 	if (IsKeyDown(KEY_H))
		// 	{
		// 		DrawModelWiresEx(*modelCube, (Vector3){0.0, 0.0, 0.0}, (Vector3){0.0, 0.0, 0.0}, 0.0, (Vector3){1.0, 1.0, 1.0}, ORANGE_SELECT);	
		// 	}
		// 	else
		// 	{
		// 		DrawModelWiresEx(*model, (Vector3){0.0, 0.0, 0.0}, (Vector3){0.0, 0.0, 0.0}, 0.0, (Vector3){1.0, 1.0, 1.0}, ORANGE_SELECT);
		// 	}
		// rlEnd();

		DrawLine3D(
			(Vector3){-50.0f, 0.0f, 0.0f},
			(Vector3){50.0f, 0.0f, 0.0f},
			(Color){ 230, 41, 55, 124 } // RED
		);
		DrawLine3D(
			(Vector3){0.0f, -50.0f, 0.0f},
			(Vector3){0.0f, 50.0f, 0.0f},
			(Color){ 0, 228, 48, 124 } // GREEN
		);
		DrawLine3D(
			(Vector3){0.0f, 0.0f, -50.0f},
			(Vector3){0.0f, 0.0f, 50.0f},
			(Color){ 0, 82, 172, 124 } // DARKBLUE
		);

		// rgizmo_draw(*gizmo, *camera, position);
	}
	EndMode3D();
}
