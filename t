/*   minishell.c                                        :+:      :+:    :+:   */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*   Created: 2022/07/03 18:43:00 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/03 21:47:19 by ael-korc         ###   ########.fr       */
#include "minishell.h"
void	handler(int signm)
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
void	ft_read_line(void)
	g.input = readline("minishell-3.2$ ");
		else
void	shlvl(void)
	while (g.env[i])
void	build_env(char **env)
	while (env[i])
	g.env = malloc((i + 1) * sizeof(char *));
	while (env[++i])
	shlvl();
	build_env(env);
	rl_catch_signals = 0;
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	while (1)
		ft_read_line();
