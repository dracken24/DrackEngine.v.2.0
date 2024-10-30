#include "struct_globale.h"
#include "../srcs/memory/dmemory.h"
#include "../../library/libft/libft.h"
#include "../../library/drackengine_lib/drackengine_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <cjson/cJSON.h>

// Function to create a directory
void create_dir(const char *chemin)
{
#ifdef DE_PLATFORM_WINDOWS
    mkdir(chemin);
#else
    mkdir(chemin, 0777);
#endif
}

// Recursive function to create the project structure
void create_arborescence(const char *cheminParent, cJSON *node, BuildProject project)
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
        if (contenu != NULL) {
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
void creerStructureProjet(const char *cheminBase, const char *jsonString, BuildProject project)
{
    cJSON *root = cJSON_Parse(jsonString);
    if (root == NULL)
    {
        printf("Erreur de parsing JSON\n");
        return;
    }

    // printf("cheminBase: %s\n", cheminBase);
    // Create the project structure
    cJSON *structure = cJSON_GetObjectItem(root, "structure");
    create_arborescence(cheminBase, structure, project);
    
    cJSON_Delete(root);
}

// int main(void)
// {
//     // Read the JSON from a file
//     FILE *file = fopen("config_files/structure_projet.json", "r");
//     if (file == NULL)
//     {
//         return 1;
//     }
    
//     // Read the content of the file
//     fseek(file, 0, SEEK_END);
//     long taille = ftell(file);
//     fseek(file, 0, SEEK_SET);
    
//     char *jsonString = malloc(taille + 1);
//     fread(jsonString, 1, taille, file);
//     jsonString[taille] = '\0';
//     fclose(file);
    
//     // Create the project structure
//     creerStructureProjet(".", jsonString);
    
//     free(jsonString);

//     return 0;
// }