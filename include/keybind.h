#ifndef KEYBIND_H
#define KEYBIND_H
#include "graphics.h"
#define KEY_MAP_SIZE 1024
typedef int (*key_fn)(int);
key_fn key_map[KEY_MAP_SIZE];

int key_quit(int c);
int key_out(int c);
int key_resize(int key);
void bind_keys();
#endif
