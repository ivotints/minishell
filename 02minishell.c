/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 02:20:41 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 21:55:16 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_env *minienv)
{
	int		exit_status;
	char	*input;
	char	**commands;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		signal_handler();
		input = trim_spaces(prompt_input(minienv));
		if (input_error(input, &exit_status, minienv))
			continue ;
		expand_input(&input, minienv, exit_status);
		if (has_pipe(input) == FALSE)
			exit_status = one_command(input, &minienv);
		else
		{
			commands = split_commands(input);
			free(input);
			exit_status = multiple_commands(commands, &minienv);
			free_array(commands);
		}
	}
	return (exit_status);
}
