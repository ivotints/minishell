/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   38execute_fork_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 02:09:54 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 20:35:36 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_forked_builtin(char **args, t_env **minienv)
{
	int	exit_status;

	exit_status = execute_builtin(args, minienv);
	free_array(args);
	free_minienv(minienv);
	rl_clear_history();
	exit(exit_status);
}

void	execute_fork_cmd(char *command, char **commands, t_env **minienv)
{
	char	**av;

	close_extra_fds();
	av = split_av(command);
	free_array(commands);
	
	if (is_builtin(av[0]))
		execute_forked_builtin(av, minienv);
	else
		execute_external(av, *minienv);
}
