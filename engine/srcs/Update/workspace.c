# include "../../includes/engine.h"
# include "../../includes/struct_globale.h"

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
	DrawGrid(10, 1.0f);

	DrawText("Try clicking on the box with your mouse!", 240, 10, 20, DARKGRAY);

	if (collision->hit)
	{
		Vector2 camera_size;
		camera_size.x = engine->allCameras->camera00.rectForCam.width;
		camera_size.y = engine->allCameras->camera00.rectForCam.height;
		DrawText("BOX SELECTED", (camera_size.x - MeasureText("BOX SELECTED", 30)) / 2, (int)(camera_size.y * 0.1f), 30, GREEN);
	}

	DrawText("Right click mouse to toggle camera controls", 10, 430, 10, GRAY);
	DrawFPS(10, 10);
}
