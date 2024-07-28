/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10heredoc_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:21 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 21:10:42 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delimiter_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !(s[i] == ' ' || s[i] == '>' || s[i] == '<' || s[i] == '|'))
	{
		if (s[i] == '\'')
		{
			delete_char(&s[i], 1);
			while (s[i] && s[i] != '\'')
				i++;
			delete_char(&s[i], 1);
		}
		else if (s[i] == '"')
		{
			delete_char(&s[i], 1);
			while (s[i] && s[i] != '"')
				i++;
			delete_char(&s[i], 1);
		}
		else
			i++;
	}
	return (i);
}

//Removes `len` characters from the string, overwriting it.
//Example:
//delete_char("Hello!\0", 1) will return "ello!\0\0"
void	delete_char(char *str, int len)
{
	ft_memmove(str, str + len, ft_strlen(str + len) + 1);
}

//Return delimiter, delete it from string
//cat -2< e | cat -e     will become
//cat -2 | cat -e
char	*get_delimiter(char *delim_pos)
{
	int		len;
	char	*delimiter;

	delete_char(delim_pos, 1);
	if (*delim_pos == '>')
		delete_char(delim_pos, 1); // it is for redirectung >> output
	while (*delim_pos == ' ')
		delete_char(delim_pos, 1);
	len = delimiter_len(delim_pos);
	delimiter = ft_substr(delim_pos, 0, len);
	delete_char(delim_pos, len);
	return (delimiter);
}

char	*get_heredoc_pos(char *str)
{
	while (str[0] && str[1])
	{
		if (*str == '\'' || *str == '"')
			str = skip_quotes(str);
		if (str[0] == '<' && str[1] == '<')
			return (str);
		str++;
	}
	return (NULL);
}

int	heredoc_handler(char *input, int *exit_status, t_env *minienv)
{
	char		*heredoc_pos;
	char		*delimiter;

	heredoc_pos = get_heredoc_pos(input);//<< e
	if (!heredoc_pos)
		return (SUCCESS);
	*heredoc_pos = 1; //1< e
	heredoc_pos++; //< e
	delimiter = get_delimiter(heredoc_pos); //e
	if (!exec_heredoc(delimiter, exit_status, minienv, input))
	{
		free(delimiter);
		return (FAILED);
	}
	free(delimiter);
	return (heredoc_handler(input, exit_status, minienv));
}
