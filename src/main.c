/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit
https://creativecommons.org/publicdomain/zero/1.0/

*/
#include "audio.h"
#include "entity.h"
#include "raylib.h"
#include "io.h"
#include "settings.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <threads.h>
#include <stdio.h>

int main() {
  // Tell the window to use vsync and work on high DPI displays
  // SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  // InitWindow(SCREENWIDTH, SCREENHEIGHT, "Hello Raylib");

  // Utility function from resource_dir.h to find the resources folder and set
  // it as the current working directory so we can load from it
  SearchAndSetResourceDir("resources");

  Entity *entities[NUM_ENT];
  for (int i = 0; i < NUM_ENT; i++) {
    entities[i] = allocate_entity("yerp", "wabbit_alpha.png",
                                  GetRandomValue(0, SCREENWIDTH),
                                  GetRandomValue(0, SCREENHEIGHT));
  }

  // text var
  char *test_string = MemAlloc(1000);
  for (int i = 0; i < 1000; i++) {
    test_string[i] = '\0';
  }

  thrd_t audio_thread, io_thread;
  thrd_create(&audio_thread, init_audio, NULL);

  // game loop
  while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or
                               // presses the Close button on the window
  {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    // draw some text using the default font
    DrawText(test_string, 200, 200, 20, WHITE);

    for (int i = 0; i < NUM_ENT; i++) {
      DrawTexture(*(entities[i]->default_texture), entities[i]->xpos,
                  entities[i]->ypos, WHITE);
      if (entities[i]->xpos + 1 >= SCREENWIDTH || entities[i]->ypos + 1 >= SCREENHEIGHT) {
        push_audio(AUDIO_FRUIT_COLLECT);
      }
      entities[i]->xpos = (entities[i]->xpos + 1) % SCREENWIDTH;
      entities[i]->ypos = (entities[i]->ypos + 1) % SCREENHEIGHT;
    }

    // DrawTexture(*(ent->default_texture), ent->xpos, ent->ypos, WHITE);
    DrawFPS(0, 0);

    // end the frame and get ready for the next one  (display frame, poll input,
    // etc...)
    EndDrawing();

    char c;
    while ((c = GetCharPressed()) != 0 && strnlen(test_string, 1000) != 999) {
      test_string[strlen(test_string)] = c;
      push_audio(AUDIO_DEFAULT);
    }
  }

  // cleanup
  for (int i = 0; i < NUM_ENT; i++) {
    deallocate_entity(entities[i]);
  }
  thrd_join(audio_thread, NULL);
  MemFree(test_string);
  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
