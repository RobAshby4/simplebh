#include "raylib.h"

typedef enum {
  AUDIO_DEFAULT,
  AUDIO_CONFIRM,
  AUDIO_FRUIT_COLLECT,
  AUDIO_END
} AudioID;

typedef struct SoundbankEntry {
  AudioID id;
  Sound loaded_sound;
  struct SoundbankEntry* next_entry;
} SoundbankEntry;

int init_audio(void* arg);

void push_audio(AudioID id);

void trim_audio();
