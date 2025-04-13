#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

typedef enum TextureID { ENT_DEFAULT, ENT_RABBIT } TextureID;
// change it to enum
//
typedef struct Entity {
  char *name;
  TextureID default_texture;
  int xpos;
  int ypos;
  int layer;
  int id;
} Entity;

Entity *allocate_entity(const char *name, TextureID texture, int xpos, int ypos,
                        int layer);

void deallocate_entity(Entity *entity);
