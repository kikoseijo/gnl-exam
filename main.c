
#include <fcntl.h>
#include <stdio.h>

#include "get_next_line.h"


int main(void)
{
	int fd = open("text.txt", O_RDONLY);

	char *line = get_next_line(fd);

	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}

	printf(">>>Finish.");
	return 1;
}
