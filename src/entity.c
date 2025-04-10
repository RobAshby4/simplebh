#include "raylib.h"
#include "./entity.h"
#include <string.h>
#include <stdio.h>

Entity* allocate_entity(const char* name, const char* texture_path, int xpos, int ypos) {
    // grab name_len to make life easy
    int name_len = strnlen(name, 100) + 1;

    // allocate entity and all of entitys fields
    Entity *new_entity = (Entity *) MemAlloc(sizeof(Entity));
    new_entity->name = MemAlloc(name_len);
    strncpy(new_entity->name, name, name_len);
    new_entity->default_texture = MemAlloc(sizeof(Texture));
    *(new_entity->default_texture) = LoadTexture(texture_path);
    new_entity->xpos = xpos;
    new_entity->ypos = ypos;

    return new_entity;
}

void deallocate_entity(Entity* entity) {
    UnloadTexture(*(entity->default_texture));
    MemFree(entity->default_texture);
    MemFree(entity->name);
    MemFree(entity);
}
