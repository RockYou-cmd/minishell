#include "minishell.h"


char	*get_next_line(int fd)
{
	char		rd[2];
	char		*res;
	int			r_rd;

	res = malloc(1);
	if (!res)
		return (NULL);
	r_rd = 1;
	res[0] = 0;
	while (!ft_strchr(res, '\n') && r_rd)
	{
		r_rd = read(fd, rd, 1);
		if (r_rd == -1 || !r_rd)
		{
			free(res);
			return (NULL);
		}
		rd[r_rd] = '\0';
        if (rd[0] == '\n')
            break ;
		res = ft_strjoin(res, rd);
	}
	return (res);
}

void	handler1()
{
	close(g.fd_stdin);
	printf("\n");
	exit (2);
}