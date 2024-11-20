/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    24-10-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE:         workspace.c             *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

#include "../../includes/engine.h"
#include "workspace.h"

// ----------------------------------------
// NOTE: Imitation de fonction template
#define SWAP_FUNCTION(T, N) \
    void swap_##T(T *a, N *b)\
	{ \
        T temp = *a; \
        *a = *b; \
        *b = temp; \
    }

SWAP_FUNCTION(int, int)
SWAP_FUNCTION(float, float)
SWAP_FUNCTION(Vector3, Vector3)

// int a = 1, b = 6;
// DE_WARNING("Avant a: %d b: %d", a, b);
// swap_int(&a, &b);
// DE_WARNING("Apres a: %d b: %d", a, b);

// ----------------------------------------

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
void	draw_grid(int slices, float spacing, Color color)
{
    int halfSlices = (int)(slices / 2);

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

void    control_main_panel(Engine *engine, Camera *camera)
{
	Model *model = &engine->testWorkspace.model;
	Model *modelCube = &engine->testWorkspace.modelCube;
	RGizmo *gizmo = &engine->testWorkspace.gizmo;
	Vector3 position = { model->transform.m12, model->transform.m13, model->transform.m14};

		// DE_DEBUG("REACH");
		// DE_DEBUG("MOUSE_STATE_ON_WORKSPACE: %d", engine->allStates.currentStateMouse);
	if (engine->allStates.currentStateMouse == MOUSE_STATE_ON_WORKSPACE || g_reset_workspace)
	{
		// DE_DEBUG("g_reset_workspace: %d", g_reset_workspace);
		if (IsKeyDown(KEY_H))
		{
			position = (Vector3){ modelCube->transform.m12, modelCube->transform.m13, modelCube->transform.m14};
			rgizmo_update(gizmo, *camera, position);
			modelCube->transform = MatrixMultiply(modelCube->transform, rgizmo_get_tranform(*gizmo, position));
		}
		else
		{
			position = (Vector3){ model->transform.m12, model->transform.m13, model->transform.m14};
			rgizmo_update(gizmo, *camera, position);
			model->transform = MatrixMultiply(model->transform, rgizmo_get_tranform(*gizmo, position));
		}

		// Release Gizmo whel leave workspace
		if (g_reset_workspace)
		{
			g_reset_workspace = false;
			if (gizmo->state > 5)
			{
				gizmo->state = RGIZMO_STATE_COLD;	
			}
		}
	}
	// DE_DEBUG("gizmo->state: %d", gizmo->state);

	ClearBackground(DARKGRAY);
	// rlEnableDepthTest();

	BeginMode3D(*camera);
	{
		DrawModel(*model, (Vector3){0.0, 0.0, 0.0}, 1.0, PURPLE);
		DrawModel(*modelCube, (Vector3){0.0, 0.0, 0.0}, 1.0, PURPLE);

		draw_grid(100.0, 1.0, GRAY);

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

		rgizmo_draw(*gizmo, *camera, position);
	}
	EndMode3D();
}
