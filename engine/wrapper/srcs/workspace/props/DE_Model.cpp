/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-29-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    DE_Model.cpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "DE_Model.hpp"

#define DrEng DrackEngine::Props
// using namespace DrackEngine::Props

DrEng::DE_Model::DE_Model(void)
{
}

DrEng::DE_Model::~DE_Model(void)
{
}

DrEng::DE_Model::DE_Model(const DE_Model& other)
{
    copyFrom(other);
}

DrEng::DE_Model& DrEng::DE_Model::operator=(const DE_Model& other)
{
    if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

void DrEng::DE_Model::copyFrom(const DE_Model& other)
{
    _model = other._model;
}
