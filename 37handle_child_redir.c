/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37handle_child_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:32:51 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:32:54 by rludvik          ###   ########.fr       */
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
