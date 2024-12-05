/* =============================================================================== */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/*               -------------------------------------------------                 */
/*                PROJET: DrackEngine   PAR: Dracken24                             */
/*               -------------------------------------------------                 */
/*                CREATED: 03-12th-2024                                            */
/*                MODIFIED BY: Dracken24                                           */
/*                LAST MODIFIED: 03-12th-2024                                      */
/*               -------------------------------------------------                 */
/*                FILE: DragDropDetect.cpp                                         */
/*               -------------------------------------------------                 */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/* =============================================================================== */

#include "DragDropDetect.hpp"

#include <algorithm>

using namespace DrackEngine::Workspace;

DragDropDetect::DragDropDetect()
{

}

DragDropDetect::DragDropDetect(const DragDropDetect& other)
{
    copyFrom(other);
}

DragDropDetect& DragDropDetect::operator=(const DragDropDetect& other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
}

DragDropDetect::~DragDropDetect()
{
    UnloadModel(_modelTest01);
    UnloadModel(_modelTest02);

    rgizmo_unload();
}

void	DragDropDetect::copyFrom(const DragDropDetect& other)
{
    _workspace = other._workspace;
    _gizmo = other._gizmo;
}

//******************************************************************************//
//***                                   Set                                  ***//
//******************************************************************************//

void	DragDropDetect::AddSceneObject(SceneObject const &sceneObject)
{
    _workspace.sceneObjects.push_back(sceneObject);
}

//******************************************************************************//
//***                                   Get                                  ***//
//******************************************************************************//

//Return a scene object or an object with name "null" and type CollisionInfo::NONE
SceneObject	DragDropDetect::GetSceneObjectByName(std::string name) const
{
    for(const auto& obj : _workspace.sceneObjects)
    {
        if (obj.name == name)
        {
            return obj;
        }
    }
    
    // Return a default object
    SceneObject objEmpty;
    objEmpty.name = "null";
    objEmpty.type = Type::NONE;

    return objEmpty;
}

//******************************************************************************//
//***                            Member functions                            ***//
//******************************************************************************//

bl8 	DragDropDetect::RemoveSceneObjectByName(std::string name)
{
    for(auto it = _workspace.sceneObjects.begin(); it != _workspace.sceneObjects.end();)
    {
        if (it->name == name)
        {
            it = _workspace.sceneObjects.erase(it);
            return true;
        }
        else
        {
            ++it;
        }
    }
    return false;
}

// Add a sceneObject in vector scene
void    DragDropDetect::AddObjectToScene(Model* model, std::string name, Type type)
{
    SceneObject newObject;
    newObject.model = model;
    newObject.type = type;
    newObject.name = name;

    _workspace.sceneObjects.push_back(newObject);
}

void    DragDropDetect::InitWorkspace(void)
{
    _gizmo = rgizmo_create();;

    // TODO: ajouter des objest tests
    Model m1 = LoadModelFromMesh(GenMeshTorus(0.3, 1.5, 16.0, 16.0));
	Model m2 = LoadModelFromMesh(GenMeshCube(1, 1, 1));
	m2.transform.m12 = -7;
	m2.transform.m13 = 3;
	m2.transform.m14 = 5;

    AddObjectToScene(&m1, "Model Torus", Type::TORUS);
    AddObjectToScene(&m2, "Model Cube", Type::CUBE);
}

std::vector<CollisionInfo> DragDropDetect::CheckUnderTheMouse(Camera *camera)
{
    std::vector<CollisionInfo> collisions;
    Vector2 mouse_position = GetMousePosition();
    Ray ray = GetMouseRay(mouse_position, *camera);

    // Check collisions for all objects in the scene
    for (auto& sceneObject : _workspace.sceneObjects)
    {
        RayCollision collision = GetRayCollisionMesh(ray, *sceneObject.model->meshes, 
            sceneObject.model->transform);
        if (collision.hit)
        {
            collisions.emplace_back(sceneObject.type, collision, sceneObject);
        }
    }

    // Sort by distance
    std::sort(collisions.begin(), collisions.end(), 
        [](const CollisionInfo& a, const CollisionInfo& b)
    {
        return a.collision.distance < b.collision.distance;
    });

    return collisions;
}
