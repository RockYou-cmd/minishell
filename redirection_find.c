#include "minishell.h"

int	spce_ned(char	*str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] != ' '
			&& str[i + 1] != str[i])
			len++;
		if ((str[i] == '>' || str[i] == '<') && str[i - 1] != ' '
			&& str[i - 1] != str[i])
			len ++;
		i ++;
	}
	return (len);
}

char	*add_spaces(char *str)
{
	int		i;
	int		t;
	char	*ret;
	int		d;
	int		s;

	i = 0;
	t = 0;
	d = 0;
	s = 0;
	ret = malloc((spce_ned(str) + ft_strlen(str) + 1) * sizeof(char));
	while (str[i])
	{
		ooc(str[i], &s, &d);
		if ((str[i] == '>' || str[i] == '<') && str[i - 1] != ' '
			&& str[i - 1] != str[i] && d == 0 && s == 0)
			ret[t ++] = ' ';
		ret[t ++] = str[i];
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] != ' '
			&& str[i + 1] != str[i] && d == 0 && s == 0)
			ret[t ++] = ' ';
		i ++;
	}
	ret[t] = 0;
	return (ret);
}

int	red_check(char *str)
{
	int		i;
	char	**ptp;
	char	*tmp;

	i = 0;
	g.t = 0;
	g.i = 0;
	tmp = add_spaces(str);
	ptp = ft_split(tmp, ' ');
	while (ptp[i])
	{
		if ((ft_strchr(ptp[i], '>') || ft_strchr(ptp[i], '<')) && (!(ft_strchr(ptp[i], '\'')) && !(ft_strchr(ptp[i], '\"'))))
		{
			if ((ft_strcmp(ptp[i], "<<") || ft_strcmp(ptp[i], ">>") || ft_strcmp(ptp[i], "<") || ft_strcmp(ptp[i], ">") ) && g.t == 0)
			{
				g.i = 1;
				g.t = 1;
			}
			else
				return (-1);
		}
		else
			g.t = 0;
		i ++;
	}
	ft_free(ptp);
	free(tmp);
	if (g.t == 1)
		return (-1);
	return (g.i);
}

void find_red(char **str, int i, int *pipe)
{
	if(ft_strcmp(str[i], "<<"))
		exec_heredoc(str[i + 1]);
	else if (ft_strcmp(str[i], ">>"))
		exec_red_output_append(str[i + 1], pipe);
	else if (ft_strcmp(str[i], "<"))
		exec_red_input(str[i + 1]);
	else if (ft_strcmp(str[i], ">"))
		exec_red_output(str[i + 1], pipe);

}

int red(char *str)
{

	if (red_check(str) == 1)
		return 1;
	else if (red_check(str) == -1)
	{
		printf("parse error\n");
		g.state = 258;
		return -1;
	}
	else
		return 0;
}
