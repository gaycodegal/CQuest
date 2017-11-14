#include "prompt.h"

void prompt_keys(){
  for(int i = 0; i < 128; ++i){
    key_map[i] = &key_write_prompt;
  }
  for(int i = 128; i < KEY_MAP_SIZE; ++i){
    key_map[i] = &key_out;
  }
  key_map[3] = &key_terminate;
  key_map[10] = &key_return_prompt;
  key_map[23] = &key_quit;
  key_map[27] = &key_quit;
  key_map[410] = &key_resize;
  key_map[263] = &key_backspace_prompt;
  key_map[260] = &key_left_prompt;
  key_map[261] = &key_right_prompt;
}

prompt *make_prompt(promptfn receiver){
  prompt *p = NEW(prompt);
  p->buffer[0] = 0;
  p->offset = 0;
  p->receiver = receiver;
  p->cursor = 0;
  p->x = 0;
  p->y = MAX_Y - 1;
  return p;
}

void draw_prompt(int x, int y, void *d){
  prompt *p = (prompt *)d;
  move(p->y, p->x);
  drawnf("> %s", MAX_X, p->buffer + p->offset);
}

void center_prompt(prompt *p){
  int o = p->cursor - MAX_X + 3;
  if(o < 0)
    o = 0;
  p->offset = o;
}

void shift_prompt(prompt *p, int forward){
  if(forward == 0){
    if(0 == p->offset)
      return;
    --(p->offset);
    return;
  }
  if(255 == p->offset || p->buffer[p->offset + 1] == 0)
      return;
    ++(p->offset);
}

int key_left_prompt(void *data, int c){
  prompt *p = (prompt *)data;
  shift_prompt(p, 0);
  redraw();
  return 0;
}

int key_right_prompt(void *data, int c){
  prompt *p = (prompt *)data;
  shift_prompt(p, 1);
  redraw();
  return 0;
}

int key_backspace_prompt(void *data, int c){
  prompt *p = (prompt *)data;
  if(p->cursor <= 0){
    beep();
    return 0;
  }
  --(p->cursor);
  center_prompt(p);
  p->buffer[p->cursor] = 0;
  redraw();
  return 0;
}

int key_return_prompt(void *data, int c){
  prompt *p = (prompt *)data;
  p->receiver(p->buffer);
  p->cursor = 0;
  p->buffer[p->cursor] = 0;
  p->offset = 0;
  
  redraw();
  return 0;
}


int key_write_prompt(void *data, int c){
  prompt *p = (prompt *)data;
  if(p->cursor >= 255){
    beep();
    return 0;
  }
  p->buffer[p->cursor] = c;
  ++(p->cursor);
  center_prompt(p);
  p->buffer[p->cursor] = 0;
  draw_prompt(0,0,p);
  return 0;
}

int prompt_input(prompt *prompt){
  int c;
  key_fn f;
  c = getch();
  if(c < 0 || c > KEY_MAP_SIZE)
    c = 0;
  f = key_map[c]; 
  if(f(prompt, c))
    return 1;
  return 0;
}

int prompttest(const char * result){
  return 0;
}

int prompt_main(){
  if(start_graphics())
    return 1;
  prompt_keys();
  prompt *p = make_prompt(&prompttest);
  add_elem(make_drawable(0, 0, p, &draw_prompt), todraw);
  redraw();
  while(!prompt_input(p));
  freeAny(p);
  end_graphics();
  return 0;
}

