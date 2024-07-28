/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33split_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:29:04 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/27 23:53:21 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_pipes(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == 3)
				*str = '|';
			str++;
		}
		exec_args++;
	}
	return ;
}

static void	replace_pipes(char *str)
{
	char	quote;

	while (*str)
	{
		while (*str && !(*str == '"' || *str == '\''))
			str++;
		if (!*str)
			return ;
		quote = *str;
		str++;
		while (*str != quote)
		{
			if (*str == '|')
				*str = 3;
			str++;
		}
		str++;
	}
}

//Pipes in quotes will be considered as a text
char	**split_commands(char *input)
{
	char	**commands;

	replace_pipes(input);
	commands = ft_split(input, '|');
	restore_pipes(commands);
	return (commands);
}
