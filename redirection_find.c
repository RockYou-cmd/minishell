#include "minishell.h"


void find_red(char **str, int i)
{
	if(ft_strcmp(str[i], "<<"))
		exec_heredoc(str[i + 1]);
	else if (ft_strcmp(str[i], ">>"))
		exec_red_output_append(str[i + 1]);
	// else if (ft_strcmp(str[i], "<"))

	else if (ft_strcmp(str[i], ">"))
		exec_red_output(str[i + 1]);

}

int red(char *str)
{

	if (red_check(str) == 1)
		return 1;
	else if (red_check(str) == -1)
	{
		printf("parse error\n");
		return -1;
	}
	else
		return 0;
	// 7ayid hadi
}
