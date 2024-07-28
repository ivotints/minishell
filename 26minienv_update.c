/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26minienv_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:50:36 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/27 21:00:27 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_keypair(char *name, char *value)
{
	char	*key_pair;
	int		key_pair_size;
	int		i;

	key_pair_size = ft_strlen(name) + ft_strlen(value) + 2;
	key_pair = malloc(key_pair_size * sizeof(char));
	i = 0;
	while (*name)
		key_pair[i++] = *name++;
	key_pair[i++] = '=';
	while (*value)
		key_pair[i++] = *value++;
	key_pair[i] = '\0';
	return (key_pair);
}

void	minienv_update(char *name, char *value, t_env *minienv)
{
	t_env	*aux;
	char	*new_pair;
	int		i;

	aux = minienv_node(name, minienv);
	if (!aux)
	{
		new_pair = create_keypair(name, value);
		minienv_add(new_pair, &minienv);
		free(new_pair);
		return ;
	}
	free(aux->key_pair);
	new_pair = malloc((ft_strlen(name) + ft_strlen(value) + 2) * sizeof(char));
	i = 0;
	while (*name)
		new_pair[i++] = *name++;
	new_pair[i++] = '=';
	while (*value)
		new_pair[i++] = *value++;
	new_pair[i] = '\0';
	aux->key_pair = new_pair;
}
