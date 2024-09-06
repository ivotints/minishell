/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06trim_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:15:59 by ivotints          #+#    #+#             */
/*   Updated: 2024/09/05 17:17:28 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Removes spaces from both sides of a string
char	*trim_spaces(char *input)
{
	char	*result;

	result = trim_spaces_no_free(input);
	free(input);
	return (result);
}

char	*trim_spaces_no_free(char *input)
{
	char	*result;
	int		i;

	while (*input == ' ')
		input++;
	i = ft_strlen(input);
	while (i > 0 && input[i - 1] == ' ')
		i--;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	result[i] = '\0';
	while (i--)
		result[i] = input[i];
	return (result);
}

void	free_array(char **av)
{
	int	i;

	if (!av)
		return ;
	i = 0;
	while (av[i])
	{
		free(av[i]);
		av[i] = NULL;
		i++;
	}
	free(av);
	av = NULL;
}
