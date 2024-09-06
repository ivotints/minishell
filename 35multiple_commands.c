/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35multiple_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:21:50 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:21:51 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_len(char **arr)
{
	int	len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

int	*init_children_pid(char **commands)
{
	int		*children_pid;
	int		size;

	size = sizeof(int) * (arr_len(commands) + 1);
	children_pid = malloc(size);
	if (!children_pid)
		return (NULL);
	ft_bzero(children_pid, size);
	return (children_pid);
}

static void	save_original_fds(int original_fds[2])
{
	original_fds[0] = dup(0);
	original_fds[1] = dup(1);
}

int	multiple_commands(char **commands, t_env **minienv)
{
	int	original_fds[2];
	int	*children_pid;
	int	i;

	save_original_fds(original_fds);
	children_pid = init_children_pid(commands);
	i = 0;
	while (commands[i])
	{
		handle_pipe(original_fds[1], commands[i], commands);
		children_pid[i] = fork();
		define_execute_signals(children_pid[i]);
		if (children_pid[i] == -1)
			print_perror_msg("fork", commands[i]);
		else if (children_pid[i] == 0)
		{
			free(children_pid);
			handle_child_redir(commands[i], commands, minienv);
			execute_fork_cmd(commands[i], commands, minienv);
		}
		i++;
	}
	restore_original_fds(original_fds);
	return (wait_for_children(children_pid));
}
