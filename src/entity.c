#include "./entity.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

int entity_id = 0;

Entity *allocate_entity(const char *name, TextureID texture, int xpos,
                        int ypos, int layer) {
  // allocate entity and all of entitys fields
  Entity *new_entity = (Entity *)MemAlloc(sizeof(Entity));
  int name_len = strnlen(name, 100) + 1;
  new_entity->name = MemAlloc(name_len);
  strncpy(new_entity->name, name, name_len);
  new_entity->default_texture = texture;
  new_entity->xpos = xpos;
  new_entity->ypos = ypos;
  new_entity->layer = layer;
  new_entity->id = ++entity_id;
  return new_entity;
}

void deallocate_entity(Entity *entity) {
  MemFree(entity->name);
  MemFree(entity);
}
