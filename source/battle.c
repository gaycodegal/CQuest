#include "battle.h"

int battle_main(){
  if(start_graphics())
    return 1;
  
  erase();
  move(0,0);
  flavor *test = make_flavor(colors[0], strdup("hello "), make_flavor(colors[1], strdup("nice (very) (ultra) (super) "), make_flavor(colors[2], strdup("day!"), NULL)));
  printncs(test, 20);
  free_flavor(test);
  while(!input_loop());
  refresh();

  end_graphics();

  return 0;
  return 0;
}
