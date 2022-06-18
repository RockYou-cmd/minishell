#include "minishell.h"

char *line(int fd)
{
	char *line;
	char *bffr = malloc(100000);
	int i;
	char c;

	i = 0;
	bffr[0] = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(bffr);
		return NULL;
	}
	while(read(fd, &c, 1) == 1)
	{
		bffr[i ++] = c;
		if (c == '\n')
			break;
	}
	if (bffr[0] == 0)
	{
		free(bffr);
		return NULL;
	}
	bffr[i] = 0;
	return bffr;

}

int main()
{
	int fd = open("data.txt", O_RDONLY);

	char *s = line(fd);
	while (s)
	{
		printf("%s", s);
		s = line(fd);
	
	}
	sleep(500);
}