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
}

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
        if (obj.name == name)
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
    if (!model)
    {
        std::cout << "Tentative d'ajout d'un modèle invalide: " << name.c_str() << std::endl;
        return;
    }

    SceneObject newObject;
    newObject.model = new Model(*model);  // Créer une copie du modèle
    newObject.type = type;
    newObject.name = name;

    _workspace.sceneObjects.push_back(newObject);
}

void    DragDropDetect::InitWorkspace(void)
{
    _gizmo = rgizmo_create();

    // TODO: ajouter des objest tests
    SceneObject torusObject;
    torusObject.model = new Model(LoadModelFromMesh(GenMeshTorus(0.3, 1.5, 16.0, 16.0)));
    torusObject.name = "Model Torus";
    torusObject.type = Type::TORUS;
    _workspace.sceneObjects.push_back(torusObject);

    SceneObject cubeObject;
    cubeObject.model = new Model(LoadModelFromMesh(GenMeshCube(1, 1, 1)));
    cubeObject.model->transform.m12 = -7;
    cubeObject.model->transform.m13 = 3;
    cubeObject.model->transform.m14 = 5;
    cubeObject.name = "Model Cube";
    cubeObject.type = Type::CUBE;
    _workspace.sceneObjects.push_back(cubeObject);
}

void    DragDropDetect::FreeWorkspace(void)
{
    // Libérer la mémoire des modèles
    for (auto& obj : _workspace.sceneObjects)
    {
        if (obj.model != nullptr)
        {
            UnloadModel(*obj.model);
            delete obj.model;
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
        // Vérification des pointeurs
        if (!sceneObject.model || !sceneObject.model->meshes)
        {
            std::cout << "Invalid model or mesh for object: " << sceneObject.name.c_str() << std::endl;
            continue;
        }

        // Debug des informations du modèle
        // Matrix mm = sceneObject.model->transform;
        // std::cout << "Checking collision for " << sceneObject.name.c_str() << std::endl;
        // std::cout << "Model transform: " << mm.m12 << " " << mm.m13 << " " << mm.m14 << std::endl; 

        RayCollision collision = GetRayCollisionMesh(ray, *sceneObject.model->meshes, 
            sceneObject.model->transform);
        
        // std::cout << "BB" << std::endl;

        if (collision.hit)
        {
            collisions.emplace_back(sceneObject.type, collision, sceneObject);
            std::cout << "HIT: " << sceneObject.name.c_str() << std::endl;
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
