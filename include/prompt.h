#ifndef PROMPT_H
#define PROMPT_H
#include "graphics.h"
#include "util.h"
#include "keybind.h"

typedef int (*promptfn)(const char *);

typedef struct s_prompt {
  int cursor;
  int x, y;
  int offset;
  char buffer[256];
  promptfn receiver;
} prompt;

void prompt_keys();
void shift_prompt(prompt *p, int forward);
void center_prompt(prompt *p);
int key_left_prompt(void *data, int c);
int key_right_prompt(void *data, int c);
int key_write_prompt(void *data, int c);
prompt *make_prompt(promptfn receiver);
void draw_prompt(int, int, void *p);
int key_backspace_prompt(void *data, int c);
int key_return_prompt(void *data, int c);
int prompt_input(prompt *p);
int prompt_main();

#endif
