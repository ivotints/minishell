/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33minienv_to_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:31:00 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:31:04 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minienv_size(t_env *minienv)
{
	int	size;

	size = 0;
	while (minienv)
	{
		size++;
		minienv = minienv->next;
	}
	return (size);
}

char	**minienv_to_envp(t_env *minienv)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (minienv_size(minienv) + 1));
	i = 0;
	while (minienv)
	{
		envp[i] = ft_strdup(minienv->key_pair);
		i++;
		minienv = minienv->next;
	}
	envp[i] = NULL;
	return (envp);
}
