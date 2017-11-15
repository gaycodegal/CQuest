#include "attacks.h"

choices * make_choices(list *opts){
  choices *c = NEW(choices);
  c->opts = opts;
  return c;
}

void *free_choices(void *data){
  choices *c = (choices *)data;
  static_map_list(c->opts, &freeAny);
  free_list(c->opts);
  free(c);
  return NULL;
}

void draw_choices(int x, int y, void *data){
  choices *c = (choices *)data;
  print_attacks(c->opts, c->combos);
}

void printline(int y, char c){
  int i;
  move(y, 0);
  for(i = 0; i < MAX_X; ++i){
    addch(c);
  }
}

void print_attacks(list * opts, map_t combos){
  node *n;
  printline(0, '=');
  n = opts->head;
  int i = 1;
  while(n != NULL){
    move(i, 0);
    drawnf("%i: %s", MAX_X, i, (char *)n->data);
    n = n->next;
    ++i;
  }
  printline(i, '=');
  
}

int attacks_receiver(const char *buffer){
  return 0;
}

int attacks_main(){
  if(start_graphics())
    return 1;
  prompt_keys();
  key_resize(NULL, 410);
  list *temp = make_list_from(3, strdup("Big Slash"), strdup("Crush"), strdup("Dazzling Heal"));
  prompt *p = make_prompt(&attacks_receiver);
  add_elem(make_drawable(0, 0, p, &draw_prompt), todraw);
  
  choices *c = make_choices(temp);
  add_elem(make_drawable(0, 0, c, &draw_choices), todraw);
  redraw();  
  while(!prompt_input(p));
  free_choices(c);
  freeAny(p);
  end_graphics();
  return 0;
}
