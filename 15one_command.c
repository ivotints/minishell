/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15one_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:09:20 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 21:54:42 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	one_command(char *input, t_env **minienv)
{
	char	**av;
	int		exit_status;
	int		original_fds[2];

	if (*input == 0)
		return (free(input), 0);
	if (!handle_redirects(input, &original_fds[0]))
	{
		restore_original_fds(original_fds);
		free(input);
		return (EXIT_FAILURE);
	}
	av = split_av(input);
	free(input);
	if (is_builtin(av[0]))
		exit_status = execute_builtin(av, minienv);
	else
		exit_status = exec_fork_extern(av, *minienv);
	free_array(av);
	restore_original_fds(original_fds);
	return (exit_status);
}
