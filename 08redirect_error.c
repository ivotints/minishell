/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08redirect_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:40:48 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/27 00:37:05 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Skip current quote
char	*skip_quotes(char *str)
{
	char	quote;

	quote = *str;
	if (quote == '\'' || quote == '"')
	{
		str++;
		while (*str != quote)
			str++;
	}
	return (str);
}

//Returns position of the next redirect (>, < or <<)
char	*get_rposition(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str = skip_quotes(str);
		if (*str == '>' || *str == '<' || *str == 1)
			return (str);
		str++;
	}
	return (str);
}

int	unexpected_token(char *input)
{
	if (input[0] == '<' && input[1] == '<')
		return (syntax_error("<<"));
	else if (input[0] == '>' && input[1] == '>')
		return (syntax_error(">>"));
	input[1] = '\0';
	return (syntax_error(input));
}

//Check *input on redirection errors
int	redirect_error(char *input)
{
	char	*position;

	position = get_rposition(input);
	if (!*position)
		return (FALSE);
	if (position[0] == '<' && position[1] == '<')
		position++;
	else if (position[0] == '>' && position[1] == '>')
		position++;
	position++;
	while (*position == ' ')
		position++;
	if (*position == '\0')
		return (syntax_error("newline"));
	if (*position == '|' || *position == '>' || *position == '<')
		return (unexpected_token(position));
	return (redirect_error(position));
}
