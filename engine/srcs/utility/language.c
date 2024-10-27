#include "../../includes/engine.h"
#include "../memory/dmemory.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>

// Utiliser des identifiants au lieu de chaînes :
// enum TextID {
//     TEXT_MENU_FILE,
//     TEXT_MENU_EDIT,
//     TEXT_MENU_VIEW,
//     // ...
// };

// const char* get_text(enum TextID id, const char* language) {
//     static const char* texts_en[] = {
//         [TEXT_MENU_FILE] = "File",
//         [TEXT_MENU_EDIT] = "Edit",
//         [TEXT_MENU_VIEW] = "View",
//         // ...
//     };
//     static const char* texts_fr[] = {
//         [TEXT_MENU_FILE] = "Fichier",
//         [TEXT_MENU_EDIT] = "Édition",
//         [TEXT_MENU_VIEW] = "Affichage",
//         // ...
//     };
    
//     if (strcmp(language, "fr") == 0) {
//         return texts_fr[id];
//     }
//     return texts_en[id]; // Par défaut, anglais
// }

// Utiliser une table de hachage pour un accès rapide :
// #include <uthash.h>

// typedef struct {
//     char* key;
//     char* value;
//     UT_hash_handle hh;
// } TextEntry;

// TextEntry* text_table = NULL;

// void add_text(const char* key, const char* value) {
//     TextEntry* entry = malloc(sizeof(TextEntry));
//     entry->key = strdup(key);
//     entry->value = strdup(value);
//     HASH_ADD_KEYPTR(hh, text_table, entry->key, strlen(entry->key), entry);
// }

// const char* get_text(const char* key) {
//     TextEntry* entry;
//     HASH_FIND_STR(text_table, key, entry);
//     return entry ? entry->value : NULL;
// }

// Utiliser un système de fichiers de ressources compilé :
// Créez un outil qui compile vos fichiers de texte en un format binaire efficace, puis chargez-le en mémoire au démarrage de votre application.

// struct TextResource {
//     uint32_t num_entries;
//     struct {
//         uint32_t key_offset;
//         uint32_t value_offset;
//     } entries[];
//     // Suivi par les données de chaîne
// };

// const char* get_text_from_resource(const struct TextResource* resource, const char* key) {
//     for (uint32_t i = 0; i < resource->num_entries; i++) {
//         const char* entry_key = (const char*)resource + resource->entries[i].key_offset;
//         if (strcmp(key, entry_key) == 0) {
//             return (const char*)resource + resource->entries[i].value_offset;
//         }
//     }
//     return NULL;
// }

// Utiliser des chaînes internées :
// #include <string.h>

// #define MAX_STRINGS 1000
// #define MAX_STRING_LENGTH 100

// char* string_pool[MAX_STRINGS] = {0};
// int string_count = 0;

// const char* intern_string(const char* str) {
//     for (int i = 0; i < string_count; i++) {
//         if (strcmp(string_pool[i], str) == 0) {
//             return string_pool[i];
//         }
//     }
//     if (string_count < MAX_STRINGS) {
//         string_pool[string_count] = strdup(str);
//         return string_pool[string_count++];
//     }
//     return NULL; // Pool plein
// }
