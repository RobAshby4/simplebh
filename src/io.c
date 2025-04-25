#include "raylib.h"
#include "entity.h"
#include "audio.h"
#include "io.h"
#include <stdio.h>



int init_io(void* args) {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Hello Raylib");
  display_loop();
  return 0;
}

void display_loop() {
  // game loop
  SetTargetFPS(60);
  while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or
                               // presses the Close button on the window
  {

    // drawing
    BeginDrawing();

    ClearBackground(BLACK);



    DrawFPS(0, 0);

    EndDrawing();
  }

  CloseWindow();
}
