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

# include "../../includes/engine.h"
# include "../../includes/struct_globale.h"

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

void    ftControlMainPanel(Engine *engine, Camera *camera)
{
	Model *model = &engine->testWorkspace.model;
	Model *modelCube = &engine->testWorkspace.modelCube;
	RGizmo *gizmo = &engine->testWorkspace.gizmo;
	Vector3 position = { model->transform.m12, model->transform.m13, model->transform.m14};

	if (IsKeyDown(KEY_H))
	{
		position = (Vector3){ modelCube->transform.m12, modelCube->transform.m13, modelCube->transform.m14};
		rgizmo_update(gizmo, *camera, position);
		modelCube->transform = MatrixMultiply(
			modelCube->transform, rgizmo_get_tranform(*gizmo, position)
		);
	}
	else
	{
		position = (Vector3){ model->transform.m12, model->transform.m13, model->transform.m14};
		rgizmo_update(gizmo, *camera, position);
		model->transform = MatrixMultiply(
			model->transform, rgizmo_get_tranform(*gizmo, position)
		);
	}


	ClearBackground(DARKGRAY);
	rlEnableDepthTest();

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
