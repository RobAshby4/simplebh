#include "entitylist.h"
#include "raylib.h"
#include <stdbool.h>
#include <threads.h>

Texture LoadedTextures;

mtx_t queue_lock;

// TODO: make it able to support multiple entity queues;

EntityQueue **alloc_entity_queue() {
  EntityQueue **entity_layers =
      (EntityQueue **)MemAlloc(sizeof(EntityQueue *) * NUM_LAYERS);
  for (int i = 0; i < NUM_LAYERS; i++) {
    entity_layers[i] = NULL;
  }
  return entity_layers;
}

void dealloc_entity_queue(EntityQueue** entity_layers) {
  flush_entity_queue(entity_layers);
}

void add_entity(Entity *entity, EntityQueue **entity_layers) {
  mtx_lock(&queue_lock);
  EntityQueue *queue_node = MemAlloc(sizeof(EntityQueue));
  queue_node->entity = entity;
  queue_node->next_ent_queue = NULL;
  int layer = entity->layer;
  if (entity_layers[layer] == NULL) {
    // if layer is empty, insert at head
    entity_layers[layer] = queue_node;
  } else {
    EntityQueue *head = entity_layers[layer];
    while (head->next_ent_queue != NULL) {
      head = head->next_ent_queue;
    }
    // should now be at end of list
    head->next_ent_queue = queue_node;
  }
  mtx_unlock(&queue_lock);
}

int remove_entity(Entity *entity, EntityQueue **entity_layers, bool locking) {
  if (locking)
    mtx_lock(&queue_lock);
  if (entity_layers[entity->layer] == NULL) {
    printf("Entity not found for removal: %s\n", entity->name);
    if (locking)
      mtx_unlock(&queue_lock);
    return -1;
  }
  EntityQueue *head = entity_layers[entity->layer];
  if (head->entity->id == entity->id) {
    // if head is the match, shift the head;
    entity_layers[entity->layer] = head->next_ent_queue;
    MemFree(head);
    if (locking)
      mtx_unlock(&queue_lock);
    return 0;
  } else {
    // if head is not the match, check until found and patch
    while (head->next_ent_queue != NULL) {
      EntityQueue *temp = head->next_ent_queue;
      if (entity->id == temp->entity->id) {
        head->next_ent_queue = temp->next_ent_queue;
        MemFree(temp);
        if (locking)
          mtx_unlock(&queue_lock);
        return 0;
      } else {
        head = temp;
      }
    }
    printf("Entity not found for removal in entire list: %s\n", entity->name);
    if (locking)
      mtx_unlock(&queue_lock);
    return -2;
  }
  if (locking)
    mtx_unlock(&queue_lock);
  return 0;
}

int flush_entity_queue(EntityQueue **entity_layers) {
  mtx_lock(&queue_lock);
  for (int i = 0; i < NUM_LAYERS; i++) {
    while (entity_layers[i] != NULL) {
      remove_entity(entity_layers[i]->entity, entity_layers, false);
    }
  }
  mtx_unlock(&queue_lock);
  return 0;
}
