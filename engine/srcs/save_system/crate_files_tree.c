#include "struct_globale.h"
#include "../srcs/memory/dmemory.h"
#include "../../library/libft/libft.h"
#include "../../library/drackengine_lib/drackengine_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <cjson/cJSON.h>

cJSON   *open_json_file(const char *jsonString);

//******************************************************************************//
//***                      create_files_tree Function                        ***//
//******************************************************************************//

// Function to create a directory
void    create_dir(const char *chemin)
{
#ifdef DE_PLATFORM_WINDOWS
	mkdir(chemin);
#else
	mkdir(chemin, 0777);
#endif
}

// Recursive function to create the project structure
void    create_arborescence(const char *cheminParent, cJSON *node, BuildProject project)
{
	char nouveauChemin[512];
	const char *type = cJSON_GetObjectItem(node, "type")->valuestring;
	char *name = cJSON_GetObjectItem(node, "nom")->valuestring;
	char *temp_name = NULL;

	// DE_DEBUG("len: %d", strcmp(name, "ProjetName"));
	if (strcmp(name, "ProjetName") == 0)
	{
		// printf("change project name: %s\n", name);

		temp_name = (char *)de_allocate(sizeof(char) * ft_strlen(project.fileNew.projectNameEntry.text) + 1, MEMORY_TAG_STRING);
		strcpy(temp_name, project.fileNew.projectNameEntry.text);
		name = temp_name;
	}
	
	// Build the new path
	snprintf(nouveauChemin, sizeof(nouveauChemin), "%s/%s", cheminParent, name);
	
	if (ft_strncmp(type, "dossier", 8) == 0)
	{
		// Create the directory
		create_dir(nouveauChemin);
		
		// Process the directory content
		cJSON *contenu = cJSON_GetObjectItem(node, "contenu");
		if (contenu != NULL)
		{
			cJSON *element;
			cJSON_ArrayForEach(element, contenu)
			{
				create_arborescence(nouveauChemin, element, project);
			}
		}
	}
	else if (strcmp(type, "fichier") == 0)
	{
		// Create an empty file
		FILE *f = fopen(nouveauChemin, "w");
		if (f != NULL)
		{
			fclose(f);
		}
	}

	if (temp_name != NULL)
	{
		de_free(temp_name, sizeof(char) * ft_strlen(project.fileNew.projectNameEntry.text) + 1, MEMORY_TAG_STRING);
	}
}

// Main function to create the project structure
void    create_structure_projet(const char *cheminBase, const char *jsonString, BuildProject project)
{
	// DE_DEBUG("JSON String reçu: %s", jsonString);
	cJSON *root = open_json_file(jsonString);
	if (root == NULL)
	{
		return;
	}
	// DE_DEBUG("JSON String reçu: %s", root->valuestring);

	// Create the project structure
	cJSON *structure = cJSON_GetObjectItem(root, "structure");
	create_arborescence(cheminBase, structure, project);
	
	cJSON_Delete(root);
}

//******************************************************************************//
//***                        JSON Globales Function                          ***//
//******************************************************************************//

// Take a json file and return all in a string
cJSON   *open_json_file(const char *jsonString)
{
	cJSON *jsonFile;
	jsonFile = cJSON_Parse(jsonString);
	if (jsonFile == NULL)
	{
		DE_WARNING("ERROR, on open json file with path: %s", jsonFile->valuestring);
		return NULL;
	}

	return jsonFile;
}

// malloc use, need to free return
char	*file_to_string(FILE *file)
{
	fseek(file, 0, SEEK_END);
	long fileLen = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	char *retour = de_allocate(sizeof(char) * fileLen + 1, MEMORY_TAG_STRING);
	
	fread(retour, 1, fileLen, file);
	retour[fileLen] = '\0';

	return retour;
}

FILE	*open_file(char const *fileName, const char *mode)
{
	FILE *file = fopen(fileName, mode);
	if (file == NULL)
	{
		DE_WARNING("Null file path open with path: %s", fileName);
		return NULL;
	}

	return file;
}

// Write a json object to a file
bl8		write_json_to_file(const char *filePath, cJSON *jsonObject)
{
	if (!jsonObject || !filePath)
	{
		DE_WARNING("Invalid parameters for writing the JSON file");
		return false;
	}

	// Convert the json object to a string
	char *jsonString = cJSON_Print(jsonObject);
	if (!jsonString)
	{
		DE_WARNING("Failed to convert JSON to string");
		return false;
	}

	// Open the file in write mode
	FILE *file = open_file(filePath, "w");
	if (!file)
	{
		DE_WARNING("Failed to open the file for writing: %s", filePath);
		cJSON_free(jsonString);
		return false;
	}

	// Write the JSON string to the file
	size_t len = strlen(jsonString);
	size_t written = fwrite(jsonString, 1, len, file);
	
	// Free the memory and close the file
	cJSON_free(jsonString);
	fclose(file);

	// Check if the writing is complete
	if (written != len)
	{
		DE_WARNING("Failed to write the complete JSON file");
		return false;
	}

	return true;
}
