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

#include "../../../../library/drackengine_lib/drackengine_lib.h"
#include "DragDropDetect.hpp"

#include <algorithm>
#include <iostream>

using namespace DrackEngine::Workspace;

DragDropDetect::DragDropDetect()
{
    _selectedObject = nullptr;
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

}

void	DragDropDetect::copyFrom(const DragDropDetect& other)
{
    _workspace = other._workspace;
    _gizmo = other._gizmo;
    _selectedObject = other._selectedObject;
}
// comment

//******************************************************************************//
//***                                   Set                                  ***//
//******************************************************************************//

void	DragDropDetect::AddSceneObject(SceneObject const &sceneObject)
{
    _workspace.sceneObjects.push_back(sceneObject);
}

void    DragDropDetect::SetSelectedObject(const std::string& name)
{
    for (auto& obj : _workspace.sceneObjects)
    {
        if (obj.GetName() == name)
        {
            _selectedObject = &obj;
            return;
        }
    }
    _selectedObject = nullptr;
}

//******************************************************************************//
//***                                   Get                                  ***//
//******************************************************************************//

//Return a scene object or an object with name "null" and type CollisionInfo::NONE
SceneObject	DragDropDetect::GetSceneObjectByName(std::string name) const
{
    for(const auto& obj : _workspace.sceneObjects)
    {
        if (obj.GetName() == name)
        {
            return obj;
        }
    }
    
    // Return a default object
    SceneObject objEmpty;
    objEmpty.SetName("null");
    objEmpty.SetType(Type::NONE);

    return objEmpty;
}

std::vector<SceneObject>    DragDropDetect::GetSceneObjects(void)
{
    return _workspace.sceneObjects;
}

void    DragDropDetect::ClearSelection()
{
    _selectedObject = nullptr;
}

SceneObject*    DragDropDetect::GetSelectedObject()
{
    return _selectedObject;
}

RGizmo  &DragDropDetect::GetGizmo()
{
    return _gizmo;
}

bl8     DragDropDetect::IsGizmoInUse() const 
{ 
    return _gizmo.state == RGIZMO_STATE_ACTIVE_ROT ||
        _gizmo.state == RGIZMO_STATE_ACTIVE_AXIS ||
        _gizmo.state == RGIZMO_STATE_ACTIVE_PLANE;
}

//******************************************************************************//
//***                            Member functions                            ***//
//******************************************************************************//

bl8 	DragDropDetect::RemoveSceneObjectByName(std::string name)
{
    for(auto it = _workspace.sceneObjects.begin(); it != _workspace.sceneObjects.end();)
    {
        if (it->GetName() == name)
        {
            it = _workspace.sceneObjects.erase(it);
            return true;
        }
        else
        {
            it++;
        }
    }
    return false;
}

// Add a sceneObject in vector scene
void    DragDropDetect::AddObjectToScene(Model* model, std::string name, Type type)
{
    if (!model)
    {
        std::cout << "Tentative d'ajout d'un modèle invalide: " << name.c_str() << std::endl;
        return;
    }

    SceneObject newObject;
    newObject.SetModel(new Model(*model));  // Create a copy
    newObject.SetType(type);
    newObject.SetName(name);

    _workspace.sceneObjects.push_back(newObject);
}

void    DragDropDetect::InitWorkspace(void)
{
    _gizmo = rgizmo_create();

    // TODO: ajouter des objest tests temporaires
    SceneObject torusObject;
    torusObject.SetModel(new Model(LoadModelFromMesh(GenMeshTorus(0.3, 1.5, 16.0, 16.0))));
    torusObject.SetName("Model Torus");
    torusObject.SetType(Type::TORUS);
    _workspace.sceneObjects.push_back(torusObject);

    SceneObject cubeObject;
    Model *m = new Model(LoadModelFromMesh(GenMeshCube(1, 1, 1)));

    m->transform.m12 = -7;
    m->transform.m13 = 3;
    m->transform.m14 = 5;

    cubeObject.SetModel(m);
    cubeObject.SetName("Model Cube");
    cubeObject.SetType(Type::CUBE);
    _workspace.sceneObjects.push_back(cubeObject);
}

void    DragDropDetect::FreeWorkspace(void)
{
    // Libérer la mémoire des modèles
    for (auto& obj : _workspace.sceneObjects)
    {
        if (obj.GetModel() != nullptr)
        {
            UnloadModel(*obj.GetModel());
            delete obj.GetModel();
        }
    }
    _workspace.sceneObjects.clear();

    rgizmo_unload();
    std::cout << "Exit DD" << std::endl;
}

std::vector<CollisionInfo> DragDropDetect::CheckUnderTheMouse(Camera *camera)
{
    // std::cout << "AAA" << std::endl;
    std::vector<CollisionInfo> collisions;
    Vector2 mouse_position = GetMousePosition();
    Ray ray = GetMouseRay(mouse_position, *camera);

    for (const auto& sceneObject : _workspace.sceneObjects)
    {
        // verification
        if (!sceneObject.GetModel() || !sceneObject.GetModel()->meshes)
        {
            std::cout << "Invalid model or mesh for object: " << sceneObject.GetName().c_str() << std::endl;
            continue;
        }

        RayCollision collision = GetRayCollisionMesh(ray, *sceneObject.GetModel()->meshes, 
            sceneObject.GetModel()->transform);

        // Collision with a SceneObject
        if (collision.hit)
        {
            collisions.emplace_back(sceneObject.GetType(), collision, sceneObject);
            std::cout << "HIT: " << sceneObject.GetName().c_str() << std::endl;
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
