#include "minishell.h"

void which_one()
{
	if (g.cmnd == 0)
		ft_echo();
	if (g.cmnd == 1)
		ft_cd();
	if (g.cmnd == 2)
		ft_pwd();
	if (g.cmnd == 3)
		ft_export();
	if (g.cmnd == 4)
		ft_unset();
	if (g.cmnd == 5)
		ft_env();
	if (g.cmnd == 6)
		ft_exit();
	
}


char *rm(char *str)
{
	int i;
	int t;
	int s;
	char *nstr;

	t = 0;
	i = 0;
	s = 0;
	nstr = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i]  != 0)
	{
		if (g.input[i] == '\'')
		{
			t = i;
			i ++;
			while(g.input[i] != '\'' && g.input[i] != 0)
				i++;
			if (g.input[i] == '\'')
			{
				t++;
				while(g.input[t] != '\'')
					nstr[s++] = g.input[t++];
			}
			else
			{
				printf("quote ' error\n");
				return 0;
			}
		}
		else if (g.input[i] == '\"')
		{
			t = i;
			i ++;
			while(g.input[i] != '\"' && g.input[i] != 0)
				i++;
			if (g.input[i] == '\"')
			{
				t++;
				while(g.input[t] != '\"')
					nstr[s++] = g.input[t++];
			}
			else
			{
				printf("quote \" error\n");
				return 0;
			}
		}
		else
			nstr[s++] = g.input[i];
		i ++;
	}
	return (nstr);
}

void check()
{
	int i;
	int t;
	int isnt;

	i = 0;
	t = 0;
	isnt = 0;
	if (g.pip == 1)
	{
		while(g.cmd->s_cmd[i + 1] != 0)
		{
			// printf("in -%s-\n",rm(g.cmd->s_cmd[i]));
			exec_v2(rm(g.cmd->s_cmd[i]));
			i ++;
		}
		exec(rm(g.cmd->s_cmd[i]));
		dup2(g.i_stdin, 0);

		// printf("-%s-\n", rm(g.cmd->s_cmd[0]));
	}
	else
		exec(g.input);
}