#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#define KEY_MAP_SIZE 1024
#define COLOR_GOOD_M 1
#define COLOR_MID_M 2
#define COLOR_LOW_M 3
#define COLOR_MAX 3
int MAX_X, MAX_Y;
short * colors;
typedef int (*key_fn)(int);
key_fn key_map[KEY_MAP_SIZE];
typedef struct s_flavor {
  struct s_flavor * next;
  short cpair;
  char * text;
} flavor;

int start_graphics();
int end_graphics();
void prints(char * s);
int printns(char * s, int n);
flavor * make_flavor(short cpair, char * text, flavor * next);
void free_flavor(flavor * f);
flavor * last_flavor(flavor * f);
char * strdup (const char *s);
void printcs(flavor * f);
int printncs(flavor * f, int n);
short * init_colors(short len);
int key_quit(int c);
int key_out(int c);
void redraw();
int key_resize(int key);
int input_loop();
int graphics_main();
#endif
