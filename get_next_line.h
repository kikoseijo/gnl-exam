
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4
#endif

char *get_next_line(int fd);

#endif
