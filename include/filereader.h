#ifndef FILEREADER_H
#define FILEREADER_H
#include <stdio.h>
#include <stdlib.h>

char * read_file(const char * filename, size_t * len);
int filereader_main();

#endif
