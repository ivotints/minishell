/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12read_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:22:48 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 21:27:16 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_string(char **input, char *var_value, char *rest_str)
{
	char	*tmp;
	char	*new_input;

	tmp = ft_strjoin(*input, var_value);
	new_input = ft_strjoin(tmp, rest_str);
	free(*input);
	free(tmp);
	*input = new_input;
}

static void	expand_variables(char **input, char *var_pos, t_env *minienv)
{
	int		l;
	char	*var_name;
	char	*var_value;

	l = 0;
	while (ft_isalnum(var_pos[l + 1]) || var_pos[l + 1] == '_')
		l++;
	var_name = ft_substr(var_pos, 1, l);
	var_value = minienv_value(var_name, minienv);
	if (!var_value)
		var_value = "";
	free(var_name);
	var_pos[0] = '\0';
	insert_string(input, var_value, var_pos + l + 1);
}


//Return pointer to a $ or to the end
char	*var_position(char *s)
{
	while (*s)
	{
		while (*s && *s != '$')
			s++;
		if (!*s)
			return (s);
		if (*s == '$' && (ft_isalnum(s[1]) || s[1] == '_' || s[1] == '?'))
			return (s);
		s++;
	}
	return (s);
}

//Expand $variabels and $? in input
void	expand_heredoc(char **input, int exit_status, t_env *minienv)
{
	char	*var_pos;
	char	*var_value;

	var_pos = var_position(*input);
	if (*var_pos)
	{
		if (var_pos[1] == '?')
		{
			var_value = ft_itoa(exit_status);
			var_pos[0] = '\0';
			insert_string(input, var_value, var_pos + 2);
			free(var_value);
		}
		else
			expand_variables(input, var_pos, minienv);
		expand_heredoc(input, exit_status, minienv);
	}
}

void	read_heredoc(int *exit_status, t_env *minienv, char *delimiter)
{
	char	*input;
	int		tmp_file_fd;

	tmp_file_fd = open("/tmp/minishell_hd", O_CREAT | O_RDWR | O_TRUNC, 0644);
	input = readline("> ");
	while (input && ft_strncmp(input, delimiter, ft_strlen(delimiter) + 1))
	{
		expand_heredoc(&input, *exit_status, minienv);
		ft_putstr_fd(input, tmp_file_fd);
		ft_putchar_fd('\n', tmp_file_fd);
		free(input);
		input = readline("> ");
	}
	if (!input)
		print_error_msg("warning: heredoc delimited by EOF. Wanted", delimiter);
	free(input);
	close(tmp_file_fd);
	free(delimiter);
	free_minienv(&minienv);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
