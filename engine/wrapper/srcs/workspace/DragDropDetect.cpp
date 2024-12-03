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
    objEmpty.type = CollisionInfo::NONE;

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
void    DragDropDetect::AddObjectToScene(Model* model, std::string name, CollisionInfo::Type type)
{
    SceneObject newObject;
    newObject.model = model;
    newObject.type = type;
    newObject.name = name;

    _workspace.sceneObjects.push_back(newObject);
}

void    DragDropDetect::InitWorkspace(void)
{
    // TODO: ajouter des objest tests
    AddObjectToScene(engine, &engine->testWorkspace.model, CollisionInfo::MODEL1);
    AddObjectToScene(engine, &engine->testWorkspace.modelCube, CollisionInfo::CUBE);
}
