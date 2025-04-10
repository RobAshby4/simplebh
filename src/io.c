#include "raylib.h"
#include "io.h"

int display_loop() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Hello Raylib");

  while (!WindowShouldClose()) {

  }
  return 0;
}
