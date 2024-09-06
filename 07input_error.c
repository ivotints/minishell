/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07input_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:08:13 by ivotints          #+#    #+#             */
/*   Updated: 2024/09/05 17:27:26 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (TRUE);
}

//Checks if *input starts from the pipe
int	pipe_start(char *input)
{
	if (*input == '|')
		return (syntax_error("|"));
	return (FALSE);
}

//Checks for unclosed quotes in *input
int	unclosed_quotes(char *input)
{
	char	last_opened;

	last_opened = '\0';
	while (*input && last_opened == 0)
	{
		if (*input == '\'' || *input == '"')
			last_opened = *input;
		input++;
	}
	while (*input && last_opened)
	{
		if (*input && *input == last_opened)
			last_opened = 0;
		input++;
	}
	if (*input)
		return (unclosed_quotes(input));
	if (last_opened == 0)
		return (FALSE);
	ft_putstr_fd("minishell: unclosed quotes detected\n", 2);
	return (TRUE);
}

int	input_error(char *input, int *exit_status, t_env *minienv)
{
	if (!*input || unclosed_quotes(input))
		return (free(input), TRUE);
	if ((pipe_start(input) || redirect_error(input) || empty_pipe(input)))
	{
		*exit_status = 2;
		return (free(input), TRUE);
	}
	if (heredoc_handler(input, exit_status, minienv) == FAILED)
		return (free(input), TRUE);
	return (FALSE);
}
