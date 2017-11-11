#include "attacks.h"

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

int attacks_main(){
  if(start_graphics())
    return 1;
  bind_keys();
  key_resize(NULL, 410);
  list *temp = make_list();
  append_elem(strdup("Big Slash"), temp);
  append_elem(strdup("Crush"), temp);
  append_elem(strdup("Dazzling Heal"), temp);
  print_attacks(temp, NULL);
  
  static_map_list(temp, &freeAny);
  free_list(temp);
  //print_attacks();
  while(!input_loop());

  end_graphics();
  return 0;
}
