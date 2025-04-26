#include "raylib.h"
#include "audio.h"
#include "io.h"
#include "entitylist.h"
#include <stdio.h>



int init_io(void* args) {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Hello Raylib");
  display_loop();
  return 0;
}

int render_entities() {

  return 0;
}

void display_loop() {
  SetTargetFPS(60);
  EntityQueue** entities = alloc_entity_list();
  for (int i = 0; i < NUM_LAYERS; i++) {
    // make entities and add them to the entityqueue
  }

  while (!WindowShouldClose())
  {

    // drawing
    BeginDrawing();

    ClearBackground(BLACK);



    DrawFPS(0, 0);

    EndDrawing();
  }

  CloseWindow();
}
