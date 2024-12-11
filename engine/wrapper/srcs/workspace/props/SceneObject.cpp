/* =============================================================================== */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/*               -------------------------------------------------                 */
/*                PROJET: DrackEngine   PAR: Dracken24                             */
/*               -------------------------------------------------                 */
/*                CREATED: 11-12th-2024                                            */
/*                MODIFIED BY: Dracken24                                           */
/*                LAST MODIFIED: 11-12th-2024                                      */
/*               -------------------------------------------------                 */
/*                FILE: SceneObject.cpp                                            */
/*               -------------------------------------------------                 */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/* =============================================================================== */

#include "SceneObject.hpp"

namespace DrackEngine::Workspace
{
	//******************************************************************************//
	//***                          Construct / Destruct                          ***//
	//******************************************************************************//

	SceneObject::SceneObject()
	{
		_model = nullptr;
	}

	SceneObject::SceneObject(const SceneObject& other)
	{
		copyFrom(other);
	}

	SceneObject& SceneObject::operator=(const SceneObject& other)
	{
		if (this != &other)
		{
			copyFrom(other);
		}
		return *this;
	}

	SceneObject::~SceneObject()
	{

	}

	void	SceneObject::copyFrom(const SceneObject& other)
	{
		_name = other._name;
		_model = other._model;
		_type = other._type;
	}

	//******************************************************************************//
	//***                                   Get                                  ***//
	//******************************************************************************//

	std::string		SceneObject::GetName(void) const
	{
		return _name;
	}

	Model*			SceneObject::GetModel(void) const
	{
		return _model;
	}

	Type			SceneObject::GetType(void) const
	{
		return _type;
	}

	//******************************************************************************//
	//***                                   Set                                  ***//
	//******************************************************************************//

	void		SceneObject::SetName(std::string name)
	{
		_name = name;
	}

	void		SceneObject::SetModel(Model* model)
	{
		_model = model;
	}

	void		SceneObject::SetType(Type type)
	{
		_type = type;
	}


	//******************************************************************************//
	//***                            Member functions                            ***//
	//******************************************************************************//
};
