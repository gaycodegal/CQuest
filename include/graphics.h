#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "keybind.h"
#include "list.h"
#define COLOR_GOOD_M 1
#define COLOR_MID_M 2
#define COLOR_LOW_M 3
#define COLOR_MAX 3
int MAX_X, MAX_Y;
short * colors;
typedef struct s_flavor {
  struct s_flavor * next;
  short cpair;
  char * text;
} flavor;

typedef void (*draw_fn)(int, int, void *);

typedef struct s_drawable {
  int x;
  int y;
  draw_fn draw;
  void *data;
} drawable;

void empty_todraw();
drawable *make_drawable(int x, int y, void *data, draw_fn draw);
list *todraw;
int drawnf(const char * fmt, int n, ...);
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
void redraw();
int input_loop();
int graphics_main();
#endif
