/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09empty_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:14:52 by ivotints          #+#    #+#             */
/*   Updated: 2024/09/05 17:26:58 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_pipe(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str = skip_quotes(str);
		if (*str == '|')
			return (str);
		str++;
	}
	return (NULL);
}

//Checks if pipeline is empty
int	empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(input);
	if (!next_pipe)
		return (FALSE);
	next_pipe++;
	while (*next_pipe == ' ')
		next_pipe++;
	if (*next_pipe == '|')
		return (syntax_error("|"));
	if (*next_pipe == '\0')
		return (ft_putstr_fd(
				"minishell: unclosed pipeline detected\n", 2), TRUE);
	return (empty_pipe(next_pipe));
}
