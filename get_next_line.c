

# include "get_next_line.h"

static int str_len(char *s)
{
	int i;

	if (!s)
		return 0;
	i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

static char *str_join(char *a, char *b, int len)
{
	int a_len = str_len(a);
	char *res = malloc((a_len + len) * sizeof(char*));
	if (!res)
		return NULL;
	int i = 0;
	while(i < a_len)
	{
		res[i] = a[i];
		i++;
	}
	i = 0;
	while(i < len)
	{
		res[a_len + i] = b[i];
		i++;
	}
	res[a_len + len] = '\0';
	return res;
}



static int line_found(char *s)
{
	int i;

	i = 0;
	if (!s)
		return -1;
	while(s[i] != '\0')
	{
		if((char) s[i] == (char) '\n')
			return ++i;
		i++;
	}
	return (-1);
}

static int readline(int fd, char **buffer)
{
	char cache[BUFFER_SIZE + 1];
	int i_read;
	int found_i;

	found_i = line_found(*buffer);
	i_read = BUFFER_SIZE;
	// printf("DEBUG\tBUFFER: %s (%d)\n", *buffer, found_i);
	while (found_i < 0 && i_read > 0)
	{
		i_read = read(fd, cache, BUFFER_SIZE);
		if (i_read == -1)
		{
			free(cache);
			return (i_read);
		}
		cache[i_read] = '\0';
		char *tmp = *buffer;
		*buffer = str_join(*buffer, cache, i_read);
		found_i = line_found(*buffer);
		printf("DEBUG\tBUFFER: %s (%d)\n", *buffer, found_i);
		free(tmp);
	}

	return (found_i);
}

static char *get_line(char **buff, int found_i)
{
	char *line;
	char *tmp = *buff;
	line = str_join("", *buff, found_i);
	// printf("DEBUG\t line: %s (%d)", line, found_i);
	if (found_i >= 0)
	{
		*buff = str_join(&(*buff)[found_i], *buff, str_len(&(*buff)[found_i]));
		free(tmp);
	}
	else
	{
		line = *buff;
		*buff = malloc(sizeof(char*));
	}
	return (line);
}

char *get_next_line(int fd)
{
	char *res;
	static char *buff;
	int found_i;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);

	// buff = malloc((BUFFER_SIZE + 1) * sizeof(char *));
	// if (!buff || read(fd, 0, 0) == -1)
	// 	return NULL;
	// buff[BUFFER_SIZE] = '\0';
	found_i = readline(fd, &buff);
	if (found_i == -1)
	{
		free(buff);
		return (NULL);
	}
	res = get_line(&buff, found_i);
	// extract_line(buff, found_i);

	return res;
}
