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
#include "../../../../library/extern/raygizmo/include/raygizmo.h"
#include "../../../core/includes/engine_defines.h"

#include "props/SceneObject.hpp"
#include "props/PropsUtility.hpp"

#include <vector>
#include <string>

namespace DrackEngine::Workspace
{
	struct CollisionInfo
	{
		Type type;
		RayCollision collision;
		std::string objectName;

		CollisionInfo(Type t, RayCollision c, const SceneObject& obj) 
			: type(t), collision(c), objectName(obj.GetName())
		{ }

		// Copy Constructor
		CollisionInfo(const CollisionInfo& other)
			: type(other.type), collision(other.collision), objectName(other.objectName)
		{ }

		CollisionInfo& operator=(const CollisionInfo& other)
		{
			if (this != &other)
			{
				type = other.type;
				collision = other.collision;
				objectName = other.objectName;
			}
			return *this;
		}

		// Fonction friend for swap
		friend void swap(CollisionInfo& a, CollisionInfo& b) noexcept
		{
			using std::swap;
			swap(a.type, b.type);
			swap(a.collision, b.collision);
			swap(a.objectName, b.objectName);
		}
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
	//***                            Members Functions                           ***//
	//******************************************************************************//

			void	ClearSelection();
			bl8		IsGizmoInUse() const;

	//******************************************************************************//
	//***                                   Set                                  ***//
	//******************************************************************************//

			void	AddSceneObject(SceneObject const &sceneObject);
			void	SetSelectedObject(const std::string& name);

	//******************************************************************************//
	//***                                   Get                                  ***//
	//******************************************************************************//

			std::vector<SceneObject>	GetSceneObjects(void);
			SceneObject		GetSceneObjectByName(std::string name) const;
			SceneObject*	GetSelectedObject();
			RGizmo			&GetGizmo();

	//******************************************************************************//
	//***                            Member functions                            ***//
	//******************************************************************************//

			bl8		RemoveSceneObjectByName(std::string name);
			void    AddObjectToScene(Model* model, std::string name, Type type);
			std::vector<CollisionInfo> CheckUnderTheMouse(Camera *camera);
			void	InitWorkspace(void);
			void    FreeWorkspace(void);

	//******************************************************************************//
	//***                                Variables                               ***//
	//******************************************************************************//

		private:
			Workspace  		_workspace;
			struct RGizmo	_gizmo;

			SceneObject*	_selectedObject;
	};
};