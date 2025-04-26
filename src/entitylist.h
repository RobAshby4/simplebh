#include "entity.h"
#include "raylib.h"
#include "settings.h"

typedef struct EntityQueue {
  Entity* entity;
  struct EntityQueue *next_ent_queue;
} EntityQueue;

EntityQueue **alloc_entity_queue();

void dealloc_entity_queue(EntityQueue **entity_layers);

void add_entity(Entity* entity, EntityQueue** entity_layers);

int remove_entity(Entity *entity, EntityQueue **entity_layers, bool locking);

int flush_entity_queue(EntityQueue **entity_layers);
