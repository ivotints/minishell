/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37handle_child_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 02:02:17 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 21:12:25 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_child(char **commands, t_env **minienv)
{
	rl_clear_history();
	free_minienv(minienv);
	free_array(commands);
	close_all_fds();
	exit(EXIT_FAILURE);
}


void	handle_child_redir(char *command, char **commands, t_env **minienv)
{
	char	redirect;

	redirect = *get_rposition(command);
	while (redirect)
	{
		if (redirect == '<')
			if (redirect_input(command) == FAILED)
				quit_child(commands, minienv);
		if (redirect == '>')
			if (redirect_output(command) == FAILED)
				quit_child(commands, minienv);
		if (redirect == 1)
			redirect_heredoc(command);
		redirect = *get_rposition(command);
	}
}
