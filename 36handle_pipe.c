/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36handle_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:32:30 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:32:39 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(int original_fd_out, char *curr_cmd, char **commands)
{
	int			is_first_command;
	int			has_next_command;
	char		*last_command;
	static int	pipe_fds[2];

	last_command = commands[arr_len(commands) - 1];
	is_first_command = (curr_cmd == commands[0]);
	has_next_command = (curr_cmd != last_command);
	if (!is_first_command)
		redirect_fd(pipe_fds[0], 0);
	if (has_next_command)
	{
		if (pipe(pipe_fds) == -1)
			print_perror_msg("pipe", curr_cmd);
		redirect_fd(pipe_fds[1], 1);
	}
	else
		redirect_fd(original_fd_out, 1);
}
