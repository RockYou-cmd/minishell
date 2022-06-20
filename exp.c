#include "minishell.h"
char *ft_len(char *str)
{
	int	i;
	int	s;
	char *rtn;

	i = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			s+=2;
		if (str[i] == '<' && str[i + 1] == '<')	
			if (str[i + 2] == '<')
			{
				printf("syntax error !\n");
				return(NULL);
			}
		if (str[i] == '>' && str[i + 1] == '>')	
			if (str[i + 2] == '>')
			{
				printf("syntax error !\n");
				return(NULL);
			}
		i++;
	}
	rtn = malloc(i + s);
	if (!rtn)
		return(NULL);
	// free(str);
	return(rtn);
}

char **add_space(char *str)
{
	int	i;
	int	s;
	char *rtn;
	char **sp;

	rtn = ft_len(str);
	if (!rtn)
		return(NULL);
	i = 0;
	s = 0;
	while(str[i])
	{
		if (str[i] != '<' || str[i] != '>')
			rtn[s++] = str[i++];
		while (str[i] == '<' || str[i] == '>')
		{
			rtn[s++] = ' ';
			if((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			{
				rtn[s++] = str[i ++];
				rtn[s++] = str[i ++];
				rtn[s++] = ' ';
				if((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
					break;
			}
			else
			{
				rtn[s++] = str[i ++];
				rtn[s++] = ' ';
			}
		}
	}
	rtn[s] = 0;
	sp = ft_split(rtn,' ');
	free(rtn);
	return(sp);
}

int main()
{
	char *str ="cat<<lk>a>b<<>'kl   '<<-e<";
	char **rtn = add_space(str);
	int i;
	i = 0;
	if (rtn)
		while(rtn[i])
			printf("%s*\n", rtn[i++]);
}