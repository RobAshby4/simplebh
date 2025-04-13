#include "entity.h"
#include "raylib.h"
#include "settings.h"

typedef struct EntityQueue {
  TextureID texture;
  Entity* entity;
  struct EntityQueue *next_ent_queue;
} EntityQueue;

EntityQueue **init_entity_queue();

void add_entity(Entity* entity);

void remove_entity(Entity* entity);
