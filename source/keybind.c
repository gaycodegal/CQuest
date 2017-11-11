#include "keybind.h"

void bind_keys(){
  for(int i = 0; i < KEY_MAP_SIZE; ++i){
    key_map[i] = &key_out;
  }
  key_map[3] = &key_terminate;
  key_map[26] = &key_quit;
  key_map[23] = &key_quit;
  key_map[27] = &key_quit;
  key_map[410] = &key_resize;
}

int key_terminate(void *data, int c){
  end_graphics();
  exit(1);
  return 1;
}

int key_quit(void *data, int c){
  return 1;
}

int key_out(void *data, int c){
  char buff[100];
  int s;
  s = snprintf(buff, 99, "%i ", c);
  buff[s] = 0;
  prints(buff);
  return 0;
}

/*
  binding to resize the screen.
 */
int key_resize(void *data, int key){
  getmaxyx(stdscr, MAX_Y, MAX_X);

  redraw();
  refresh();

  return 0;
}
