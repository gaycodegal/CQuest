#ifndef KEYBIND_H
#define KEYBIND_H
#include "graphics.h"
#define KEY_MAP_SIZE 1024
typedef int (*key_fn)(void *, int);
key_fn key_map[KEY_MAP_SIZE];

int key_terminate(void *, int c);
int key_quit(void *, int c);
int key_out(void *, int c);
int key_resize(void *, int key);
void bind_keys();

#endif
