#include "entitylist.h"
#include "raylib.h"
#include <threads.h>

EntityQueue* entity_layers[NUM_LAYERS];

Texture LoadedTextures;

mtx_t queue_lock;

EntityQueue** init_entity_queue() {
  mtx_lock(&queue_lock);
  for (int i = 0; i < NUM_LAYERS; i++){
    entity_layers[i] = NULL;
  }
  mtx_unlock(&queue_lock);
  return entity_layers;
}

void add_entity(Entity* entity) {
  mtx_lock(&queue_lock);
  EntityQueue* queue_node = MemAlloc(sizeof(EntityQueue));
  queue_node->entity = entity;
  queue_node->texture = entity->default_texture;
  queue_node->next_ent_queue = NULL;
  int layer = entity->layer;
  if (entity_layers[layer] == NULL) {
    // if layer is empty, insert at head
    entity_layers[layer] = queue_node;
  } else {
    EntityQueue* head = entity_layers[layer];
    while (head->next_ent_queue != NULL) {
      head = head->next_ent_queue;
    }
    // should now be at end of list
    head->next_ent_queue = queue_node;
  }
  mtx_unlock(&queue_lock);
}
