#include <stdio.h>
#include "graphics.h"
#include "battle.h"
#include "filereader.h"
#include "attacks.h"
#include "util.h"
#include "prompt.h"

typedef int (*mainfn)();

mainfn *make_mptr(mainfn fn){
  mainfn *p = NEW(mainfn);
  *p = fn;
  return p;
}

int free_mptr(void *item, void *data){
  free(data);
  return MAP_OK;
}

int main(int argc, char **argv){
  int status = MAP_MISSING;
  map_t *mains_map;
  mainfn f;
  any_t p[1];
  mains_map = hashmap_new();
  hashmap_put(mains_map, "battle", make_mptr(&battle_main));
  hashmap_put(mains_map, "graphics", make_mptr(&graphics_main));
  hashmap_put(mains_map, "filereader", make_mptr(&filereader_main));
  hashmap_put(mains_map, "attacks", make_mptr(&attacks_main));
  hashmap_put(mains_map, "prompt", make_mptr(&prompt_main));
  if(argc == 2)
    status = hashmap_get(mains_map, argv[1], p);
  if(status != MAP_OK){
    printf("usage: %s <mode>\n", *argv);
    printf("modes: battle, graphics, filereader, attacks, prompt\n");
    return 1;
  }else{
    f = *(mainfn *)*p;
    status = f();
  }
  hashmap_iterate(mains_map, &free_mptr, NULL);
  hashmap_free(mains_map);
  return status;
}
