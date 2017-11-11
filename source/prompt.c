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
}

prompt *make_prompt(promptfn receiver){
  prompt *p = NEW(prompt);
  p->buffer[0] = 0;
  p->offset = p->buffer;
  p->receiver = receiver;
  p->cursor = 0;
  p->x = 0;
  p->y = MAX_Y - 1;
  return p;
}

void display_prompt(int x, int y, void *d){
  prompt *p = (prompt *)d;
  move(p->y, p->x);
  drawnf("> %s", MAX_X, p->offset);
}

int key_backspace_prompt(void *data, int c){
  prompt *p = (prompt *)data;
  if(p->cursor <= 0){
    beep();
    return 0;
  }
  --(p->cursor);
  p->buffer[p->cursor] = 0;
  erase();
  display_prompt(0,0,p);
  return 0;
}

int key_return_prompt(void *data, int c){
  prompt *p = (prompt *)data;
  p->receiver(p->buffer);
  p->cursor = 0;
  p->buffer[p->cursor] = 0;
  
  erase();
  display_prompt(0,0,p);
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
  p->buffer[p->cursor] = 0;
  display_prompt(0,0,p);
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
  key_resize(NULL, 410);
  prompt *p = make_prompt(&prompttest);
  display_prompt(0,0,p);
  //print_attacks();
  while(!prompt_input(p));
  
  end_graphics();
  return 0;
}

