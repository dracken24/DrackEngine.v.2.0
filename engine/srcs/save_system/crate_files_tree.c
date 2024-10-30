#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <cjson/cJSON.h>

// Function to create a directory
void creer_dossier(const char *chemin)
{
#ifdef _WIN32
    mkdir(chemin);
#else
    mkdir(chemin, 0777);
#endif
}

// Recursive function to create the project structure
void create_arborescence(const char *cheminParent, cJSON *node)
{
    char nouveauChemin[512];
    const char *type = cJSON_GetObjectItem(node, "type")->valuestring;
    const char *nom = cJSON_GetObjectItem(node, "nom")->valuestring;
    
    // Build the new path
    snprintf(nouveauChemin, sizeof(nouveauChemin), "%s/%s", cheminParent, nom);
    
    if (strcmp(type, "dossier") == 0)
    {
        // Create the directory
        creer_dossier(nouveauChemin);
        
        // Process the directory content
        cJSON *contenu = cJSON_GetObjectItem(node, "contenu");
        if (contenu != NULL) {
            cJSON *element;
            cJSON_ArrayForEach(element, contenu)
            {
                create_arborescence(nouveauChemin, element);
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
}

// Main function to create the project structure
void creerStructureProjet(const char *cheminBase, const char *jsonString)
{
    cJSON *root = cJSON_Parse(jsonString);
    if (root == NULL)
    {
        printf("Erreur de parsing JSON\n");
        return;
    }
    
    // Create the project root directory
    char cheminProjet[512];
    const char *nomProjet = cJSON_GetObjectItem(root, "nomProjet")->valuestring;
    snprintf(cheminProjet, sizeof(cheminProjet), "%s/%s", cheminBase, nomProjet);
    creer_dossier(cheminProjet);
    
    // Create the project structure
    cJSON *structure = cJSON_GetObjectItem(root, "structure");
    create_arborescence(cheminBase, structure);
    
    cJSON_Delete(root);
}

// Example of use
int main(void)
{
    // Read the JSON from a file
    FILE *file = fopen("config_files/structure_projet.json", "r");
    if (file == NULL)
    {
        return 1;
    }
    
    // Read the content of the file
    fseek(file, 0, SEEK_END);
    long taille = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *jsonString = malloc(taille + 1);
    fread(jsonString, 1, taille, file);
    jsonString[taille] = '\0';
    fclose(file);
    
    // Create the project structure
    creerStructureProjet(".", jsonString);
    
    free(jsonString);

    return 0;
}