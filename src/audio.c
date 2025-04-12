#include "audio.h"
#include "raylib.h"
#include <stdio.h>
#include <threads.h>
#include <time.h>

#define MAX_AUDIO_QUEUE 1000

char *sound_path[] = {"Text 1.wav", "Confirm 1.wav", "Fruit collect 1.wav"};
SoundbankEntry *sound_bank[AUDIO_END];

// circlular buffer
// TODO: might be better to make a linked list queue? idk depends
AudioID audio_queue[MAX_AUDIO_QUEUE];
mtx_t queue_lock;


// push from head read from tail
int queue_head = 0;
int queue_tail = 0;
int queue_len = 0;

SoundbankEntry *allocate_soundbank_entry(AudioID id) {
  SoundbankEntry *new_entry = MemAlloc(sizeof(SoundbankEntry));
  new_entry->id = id;
  new_entry->loaded_sound = LoadSound(sound_path[id]);
  new_entry->next_entry = NULL;
  return new_entry;
}

void deallocate_soundbank_entry(SoundbankEntry *entry) {
  UnloadSound(entry->loaded_sound);
  MemFree(entry);
}

int init_audio(void *arg) {
  InitAudioDevice();
  SetAudioStreamBufferSizeDefault(4096);
  for (int i = 0; i < AUDIO_END; i++) {
    sound_bank[i] = allocate_soundbank_entry(i);
  }
  mtx_init(&queue_lock, mtx_plain);
  while (!WindowShouldClose()) {
    // grab lock to avoid race conditions
    mtx_lock(&queue_lock);

    while (queue_len > 0) {
      // PlaySound(); <- needs to be changed
      AudioID queue_id = audio_queue[queue_tail];
      SoundbankEntry *temp_entry = sound_bank[queue_id];
      while (IsSoundPlaying(temp_entry->loaded_sound)) {
        // if null, allcoate new sound as we ran out of non-playing sounds!!!
        if (temp_entry->next_entry == NULL) {
          SoundbankEntry *new_sound = allocate_soundbank_entry(queue_id);
          // avoid creating orphans
          new_sound->next_entry = temp_entry->next_entry;
          temp_entry->next_entry = new_sound;
        }
        temp_entry = temp_entry->next_entry;
      }
      PlaySound(temp_entry->loaded_sound);
      queue_len -= 1;
      queue_tail = (queue_tail + 1) % MAX_AUDIO_QUEUE;
    }
    mtx_unlock(&queue_lock);

    // sleep to avoid pegging thread at 100% cpu, may cause audio choppyness
    thrd_sleep(&(struct timespec){.tv_nsec = 1}, NULL); // sleep 1 nanosec
  }

  // cleanup soundbank
  for (int i = 0; i < AUDIO_END; i++) {
    // free linked list for audio bank entry
    SoundbankEntry *entry = sound_bank[i];
    while (entry != NULL) {
      printf("INFO: Unloading sound\n");
      SoundbankEntry *next_entry = entry->next_entry;
      deallocate_soundbank_entry(entry);
      entry = next_entry;
    }
  }
  return 0;
}

void push_audio(AudioID id) {
  // grab lock to avoid race conditions
  mtx_lock(&queue_lock);
  if (queue_len < MAX_AUDIO_QUEUE - 1) {
    audio_queue[queue_head] = id;
    queue_len += 1;
    queue_head = (queue_head + 1) % MAX_AUDIO_QUEUE;
    mtx_unlock(&queue_lock);
  } else {
    // handle deadlock
    mtx_unlock(&queue_lock);
    // could cause major performance issues if queue is fully filled. probably
    // wont happen though.
    push_audio(id);
  }
}

// reduce number of sound effects if it gets to gnarly, useful for things like
// scene/level change
void trim_audio() {
  // grab lock to avoid race conditions
  mtx_lock(&queue_lock);
  for (int i = 0; i < AUDIO_END; i++) {
    // free linked list for audio bank entry
    // start entry at the second member for each entry
    SoundbankEntry *entry = sound_bank[i];
    entry = entry->next_entry;
    while (entry != NULL) {
      SoundbankEntry *next_entry = entry->next_entry;
      deallocate_soundbank_entry(entry);
      entry = next_entry;
    }
  }
  mtx_unlock(&queue_lock);
}
