/* =============================================================================== */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/*               -------------------------------------------------                 */
/*                PROJET: DrackEngine   PAR: Dracken24                             */
/*               -------------------------------------------------                 */
/*                CREATED: 03-12th-2024                                            */
/*                MODIFIED BY: Dracken24                                           */
/*                LAST MODIFIED: 03-12th-2024                                      */
/*               -------------------------------------------------                 */
/*                FILE: DragDropDetect.hpp                                         */
/*               -------------------------------------------------                 */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/* =============================================================================== */

#pragma once

#include "raylib.h"
#include "../../../library/extern/raygizmo/include/raygizmo.h"

#include "../../core/includes/engine_defines.h"

#include <vector>
#include <string>

namespace DrackEngine::Workspace
{
	struct CollisionInfo
	{
		enum Type
		{
			NONE,
			MODEL,
			MESH,
			TRIANGLE,
			CUBE,
			SPHERE,
			PLANE
		};
		
		Type type;
		RayCollision collision;
	};

	struct SceneObject
	{
		std::string			name;

		Model*				model;
		CollisionInfo::Type type;
	};

	struct Workspace
	{
		std::vector<SceneObject> sceneObjects;  // Collection for all objects in the scene
	};

	// For Drag, drop and detect under the mouse events
	class DragDropDetect
	{
		public:
	//******************************************************************************//
	//***                          Construct / Destruct                          ***//
	//******************************************************************************//

			DragDropDetect();
			DragDropDetect(const DragDropDetect&);
			DragDropDetect& operator=(const DragDropDetect&);
			~DragDropDetect();

			void	copyFrom(const DragDropDetect& other);

	//******************************************************************************//
	//***                                   Set                                  ***//
	//******************************************************************************//

			void	AddSceneObject(SceneObject const &sceneObject);

	//******************************************************************************//
	//***                                   Get                                  ***//
	//******************************************************************************//

			SceneObject	GetSceneObjectByName(std::string name) const;

	//******************************************************************************//
	//***                            Member functions                            ***//
	//******************************************************************************//

			bl8		RemoveSceneObjectByName(std::string name);
			void    AddObjectToScene(Model* model, std::string name, CollisionInfo::Type type);

		private:
			Workspace   _workspace;
			struct RGizmo	_gizmo;

			void	InitWorkspace(void);
	};
};