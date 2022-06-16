#include "minishell.h"

int left_heredoc(char **str, int i)
{
	exec_heredoc(str[i + 1]);
	return i;
}
int right_heredoc(char **str, int i)
{
		printf("right he -%s-\n", str[i + 1]);
	return i;
}
int left_red(char **str, int i)
{

		printf("left red -%s-\n", str[i + 1]);

	return i;
}
int right_red(char **str, int i)
{
		printf("right red -%s-\n", str[i + 1]);

	return i;

}
void find_red(char **str, int i)
{
	if(ft_strcmp(str[i], "<<"))
		left_heredoc(str, i);
	else if (ft_strcmp(str[i], ">>"))
		right_heredoc(str, i);
	else if (ft_strcmp(str[i], "<"))
		left_red(str, i);
	else if (ft_strcmp(str[i], ">"))
		right_red(str, i);
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
