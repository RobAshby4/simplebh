#include "raylib.h"
#include "settings.h"

typedef struct IOArgs {
  int* input_buff;
  int* output_buff;
  // TODO: need to make output buffer datatype for depth reasons
} IOArgs;

int init_io(void* args);

void display_loop();
