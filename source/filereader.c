#include "filereader.h"

char * read_file(const char * filename, size_t * len){
  char * contents;
  FILE * fp = fopen(filename, "rb");
  size_t sz;
  fseek(fp, 0L, SEEK_END);
  sz = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  contents = (char *)malloc(sizeof(char) * (sz + 1));
  fread((void *)contents, 1, sz, fp);
  contents[sz] = 0;
  *len = sz;
  return contents;
}

int filereader_main(){
  size_t s;
  char * contents = read_file("../test.txt", &s);
  printf("%ld '%s'\n",s,contents);
  free(contents);
  return 0;
}
