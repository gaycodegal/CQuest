#ifndef PROMPT_H
#define PROMPT_H
#include "graphics.h"
#include "util.h"
#include "keybind.h"

typedef int (*promptfn)(const char *);

typedef struct s_prompt {
  int cursor;
  int x, y;
  char *offset;
  char buffer[256];
  promptfn receiver;
} prompt;

int key_write_prompt(void *data, int c);
prompt *make_prompt(promptfn receiver);
void display_prompt(int, int, void *p);
int key_backspace_prompt(void *data, int c);
int key_return_prompt(void *data, int c);
int prompt_input();
int prompt_main();

#endif
