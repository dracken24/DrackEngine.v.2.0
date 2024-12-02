/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-29-2024           *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    DE_Model.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#pragma once

#include "raylib.h"
// #include "raymath.h"

namespace DrackEngine::Props
{
	class DE_Model
	{
		public:
			DE_Model(void);
			~DE_Model(void);
			DE_Model(const DE_Model& other);
			DE_Model& operator=(const DE_Model& other);

		private:
			void	copyFrom(const DE_Model& other);    
		
		private:
			Model   _model;
	}; 
};

//*****************************************************************/
//************************** From Raylib **************************/
//*****************************************************************/
// typedef struct Model
// {
//     Matrix transform;       // Local transform matrix

//     int meshCount;          // Number of meshes
//     int materialCount;      // Number of materials
//     Mesh *meshes;           // Meshes array
//     Material *materials;    // Materials array
//     int *meshMaterial;      // Mesh material number

//     // Animation data
//     int boneCount;          // Number of bones
//     BoneInfo *bones;        // Bones information (skeleton)
//     Transform *bindPose;    // Bones base transformation (pose)
// } Model;
