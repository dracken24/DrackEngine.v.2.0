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

#include <vector>
#include <string>

namespace DrackEngine::Workspace
{
	enum Type
	{
		NONE,
		MODEL,
		MESH,
		TORUS,
		TRIANGLE,
		CUBE,
		SPHERE,
		PLANE
	};

	struct SceneObject
	{
		std::string			name;

		Model*				model;
		Type type;
	};

	struct CollisionInfo
	{
		Type type;
		RayCollision collision;

		SceneObject	&sceneObject;

		// Default contructor
		CollisionInfo(Type t, RayCollision c, SceneObject& obj) 
			: type(t), collision(c), sceneObject(obj)
		{ }

		// Copy Constructor
		CollisionInfo(const CollisionInfo& other)
			: type(other.type), collision(other.collision), sceneObject(other.sceneObject)
		{ }

		// Overload affectation 
		CollisionInfo& operator=(const CollisionInfo& other)
		{
			if (this != &other)
			{
				type = other.type;
				collision = other.collision;
				sceneObject = other.sceneObject;
			}
			return *this;
		}

		// Fonction friend for swap
		friend void swap(CollisionInfo& a, CollisionInfo& b) noexcept
		{
			using std::swap;
			swap(a.type, b.type);
			swap(a.collision, b.collision);
			SceneObject& tempRef = a.sceneObject;
			a.sceneObject = b.sceneObject;
			b.sceneObject = tempRef;
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
			void    AddObjectToScene(Model* model, std::string name, Type type);
			std::vector<CollisionInfo> CheckUnderTheMouse(Camera *camera);

		private:
			Workspace   _workspace;
			struct RGizmo	_gizmo;

			Model	_modelTest01;
			Model	_modelTest02;

			void	InitWorkspace(void);
	};
};