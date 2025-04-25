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

  thrd_t audio_thread, io_thread;
  thrd_create(&io_thread, init_io, NULL);
  thrd_create(&audio_thread, init_audio, NULL);

  thrd_join(io_thread, NULL);
  thrd_join(audio_thread, NULL);
  return 0;
}
