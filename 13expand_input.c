/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13expand_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:42:07 by ivotints          #+#    #+#             */
/*   Updated: 2024/09/05 17:20:04 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_var_position(char *input)
{
	while (*input)
	{
		if (*input == '\'')
			input = skip_quotes(input);
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && (ft_isalnum(input[1]) || input[1] == '_'))
					return (input);
				input++;
			}
		}
		if (*input == '$' && (ft_isalnum(input[1]) || input[1] == '_'))
			return (input);
		input++;
	}
	return (NULL);
}

static void	expand_variables(char **input, t_env *minienv)
{
	char	*var_position;
	char	*var_name;
	char	*var_value;
	int		l;

	var_position = find_var_position(*input);
	if (var_position)
	{
		l = 0;
		while (ft_isalnum(var_position[l + 1]) || var_position[l + 1] == '_')
			l++;
		var_name = ft_substr(var_position, 1, l);
		*var_position = '\0';
		var_value = minienv_value(var_name, minienv);
		if (!var_value)
			var_value = "";
		free(var_name);
		insert_string(input, var_value, (var_position + 1 + l));
		expand_variables(input, minienv);
	}
}

static char	*find_exit_status_position(char *input)
{
	while (*input)
	{
		if (*input == '\'')
			input = skip_quotes(input);
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && input[1] == '?')
					return (input);
				input++;
			}
		}
		if (*input == '$' && input[1] == '?')
			return (input);
		input++;
	}
	return (NULL);
}

static void	expand_exit_status(char **input, int exit_status)
{
	char	*exit_pos;
	char	*exit_str;

	exit_pos = find_exit_status_position(*input);
	if (exit_pos)
	{
		*exit_pos = '\0';
		exit_str = ft_itoa(exit_status);
		insert_string(input, exit_str, (exit_pos + 2));
		free(exit_str);
		expand_exit_status(input, exit_status);
	}
}

void	expand_input(char **input, t_env *minienv, int exit_status)
{
	expand_exit_status(input, exit_status);
	expand_variables(input, minienv);
}
