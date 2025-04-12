#include "raylib.h"
#include "entity.h"
#include "audio.h"
#include "io.h"
#include <stdio.h>

Entity *entities[NUM_ENT];
char test_string[1000];

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
  printf("running loop");
  for (int i = 0; i < NUM_ENT; i++) {
    entities[i] = allocate_entity("yerp", "wabbit_alpha.png",
                                  GetRandomValue(0, SCREENWIDTH),
                                  GetRandomValue(0, SCREENHEIGHT));
  }

  // text var
  for (int i = 0; i < 1000; i++) {
    test_string[i] = '\0';
  }
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
  // destroy the window and cleanup the OpenGL context
  CloseWindow();
}
