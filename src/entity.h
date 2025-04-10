#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

typedef struct Entity {
  Texture *default_texture;
  char *name;
  int xpos;
  int ypos;
} Entity;

Entity *allocate_entity(const char *name, const char *texture_path, int xpos,
                        int ypos);

void deallocate_entity(Entity *entity);
