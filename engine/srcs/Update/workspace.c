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

void draw_gizmo(Vector3 position, float scale)
{
    // Dessiner l'axe X en rouge
    DrawLine3D(position, (Vector3){ position.x + scale, position.y, position.z }, RED);
    // Dessiner l'axe Y en vert
    DrawLine3D(position, (Vector3){ position.x, position.y + scale, position.z }, GREEN);
    // Dessiner l'axe Z en bleu
    DrawLine3D(position, (Vector3){ position.x, position.y, (position.z + scale) * -1 }, BLUE);
}

void    ftControlMainPanel(Engine *engine)
{
	Camera3D *camera = &engine->allCameras->camera00.camera3D;
    Vector3 *cubePosition = &engine->testWorkspace.cubePosition;
    Vector3 *cubeSize = &engine->testWorkspace.cubeSize;
    Ray *ray = &engine->testWorkspace.ray;
    RayCollision *collision = &engine->testWorkspace.collision;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (!collision->hit)
		{
			*ray = GetScreenToWorldRay(GetMousePosition(), *camera);

			// Check collision between ray and box
			*collision = GetRayCollisionBox(*ray,
						(BoundingBox){(Vector3){ cubePosition->x - cubeSize->x/2, cubePosition->y - cubeSize->y/2, cubePosition->z - cubeSize->z/2 },
										(Vector3){ cubePosition->x + cubeSize->x/2, cubePosition->y + cubeSize->y/2, cubePosition->z + cubeSize->z/2 }});
		}
		else
		{
			collision->hit = false;
		}
	}

	//----------------------------------------------------------------------------------

	if (collision->hit)
	{
		DrawCube(*cubePosition, cubeSize->x, cubeSize->y, cubeSize->z, RED);
		DrawCubeWires(*cubePosition, cubeSize->x, cubeSize->y, cubeSize->z, MAROON);

		DrawCubeWires(*cubePosition, cubeSize->x + 0.2f, cubeSize->y + 0.2f, cubeSize->z + 0.2f, GREEN);
	}
	else
	{
		DrawCube(*cubePosition, cubeSize->x, cubeSize->y, cubeSize->z, GRAY);
		DrawCubeWires(*cubePosition, cubeSize->x, cubeSize->y, cubeSize->z, DARKGRAY);
	}

	DrawRay(*ray, MAROON);
	DrawGrid(20, 1.0f);
	// Draw gizmo on upper right corner
	draw_gizmo((Vector3){0, 0, 0}, 1);

	// DrawText("Try clicking on the box with your mouse!", 240, 10, 20, DARKGRAY);

	if (collision->hit)
	{
		Vector2 camera_size;
		camera_size.x = engine->allCameras->camera00.rectForCam.width;
		camera_size.y = engine->allCameras->camera00.rectForCam.height;
		// DrawText("BOX SELECTED", (camera_size.x - MeasureText("BOX SELECTED", 30)) / 2, (int)(camera_size.y * 0.1f), 30, GREEN);
	}
	DrawTextPro(engine->fonts.defaultFont, "Tesxt Test", (Vector2){10, 10}, (Vector2){0, 0}, 20, 60, 1, BLACK);

	// DrawText("Right click mouse to toggle camera controls", 10, 430, 10, GRAY);
	// DrawFPS(10, 10);

	// Rotate around center point
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		Vector3 cameraLastPosition = camera->position;
		UpdateCamera(camera, CAMERA_FREE);

		float moveSpeed = 1.0f; // Vitesse de déplacement normale
		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			moveSpeed = 4.0f; // Augmentez la vitesse de déplacement
			// DE_WARNING("Vitesse de déplacement: %f", moveSpeed);
		}

		// Appliquez la vitesse de déplacement à la position de la caméra
		Vector3 direction = Vector3Subtract(camera->position, cameraLastPosition);
		direction = Vector3Scale(direction, moveSpeed);
		camera->position = Vector3Add(cameraLastPosition, direction);
		
		UpdateCamera(camera, CAMERA_FREE);
	}
	// DE_WARNING("Camera pos x: %f y: %f z: %f", camera->position.x, camera->position.y, camera->position.z);
}
