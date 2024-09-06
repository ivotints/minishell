/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20split_av.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:27:54 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:28:00 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_spaces(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == 2)
				*str = ' ';
			str++;
		}
		exec_args++;
	}
	return ;
}

static void	remove_quotes(char *str)
{
	char	last_opened;

	last_opened = 0;
	while (*str && last_opened == 0)
	{
		if (*str == '\'' || *str == '"')
		{
			last_opened = *str;
			delete_char(str, 1);
		}
		else
			str++;
	}
	while (*str && last_opened)
	{
		if (*str && *str == last_opened)
		{
			last_opened = 0;
			delete_char(str, 1);
		}
		else
			str++;
	}
	if (*str)
		return (remove_quotes(str));
}

static void	replace_spaces(char *str, char delimeter)
{
	while (*str && *str != delimeter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimeter)
	{
		if (*str == ' ')
			*str = 2;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		replace_spaces(str, delimeter);
}

char	**split_av(char *input)
{
	char	**av;

	replace_spaces(input, '"');
	replace_spaces(input, '\'');
	remove_quotes(input);
	av = ft_split(input, ' ');
	restore_spaces(av);
	return (av);
}
