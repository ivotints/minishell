/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04prompt_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:54:38 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 18:14:59 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strlncat(char *dest, const char *src, const char *end, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dest);
	if (size <= j)
		return ;
	while (((j + i + 1) < size) && (src[i]) && &src[i] < end)
	{
		dest[j + i] = src[i];
		i++;
	}
	if (j < size)
		dest[j + i] = '\0';
}

// to get cool prompt
static char	*get_prompt_str(t_env *minienv)
{
	char		*info;
	static char	prompt[PATH_MAX];

	ft_bzero(prompt, sizeof(prompt));
	ft_strlcat(prompt, GREEN, PATH_MAX);
	info = minienv_value("USER", minienv);
	if (!info)
		info = "USER";
	ft_strlcat(prompt, info, PATH_MAX);
	ft_strlcat(prompt, "@", PATH_MAX);
	info = minienv_value("SESSION_MANAGER", minienv);
	if (info)
		ft_strlncat(prompt, info + 6, ft_strchr(info, ':'), PATH_MAX);
	else
		ft_strlcat(prompt, "42Prague", PATH_MAX);
	ft_strlcat(prompt, RESET, PATH_MAX);
	ft_strlcat(prompt, ":", PATH_MAX);
	ft_strlcat(prompt, RED, PATH_MAX);
	info = minienv_value("PWD", minienv);
	if (!info)
		info = "/WORKING_DIRECTORY";
	ft_strlcat(prompt, ft_strrchr(info, '/') + 1, PATH_MAX);
	ft_strlcat(prompt, RESET, PATH_MAX);
	ft_strlcat(prompt, "$ ", PATH_MAX);
	return (prompt);
}

char	*prompt_input(t_env *minienv)
{
	char	*input;

	input = readline(get_prompt_str(minienv)); // or just "minishell$ "
	if (!input)
		builtin_exit(NULL, &minienv); // to manage Ctrl D
	if (*input)
		add_history(input);
	return (input);
}
