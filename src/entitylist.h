#include "entity.h"
#include "raylib.h"
#include "settings.h"

typedef struct EntityQueue {
  Entity* entity;
  struct EntityQueue *next_ent_queue;
} EntityQueue;

EntityQueue **init_entity_queue();

void add_entity(Entity* entity);

int remove_entity(Entity* entity);
