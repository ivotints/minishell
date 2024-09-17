/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01init_minienv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:03:43 by ivotints          #+#    #+#             */
/*   Updated: 2024/09/17 19:12:56 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Search for *name in *minienv
t_env	*minienv_node(char *name, t_env *minienv)
{
	t_env	*aux;
	int		size;

	aux = minienv;
	size = ft_strlen(name);
	while (aux)
	{
		if (ft_strncmp(name, aux->key_pair, size) == 0)
			if (aux->key_pair[size] == '=')
				return (aux);
		aux = aux->next;
	}
	return (NULL);
}

//Return value of *key_pair
char	*value_only(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (&key_pair[i + 1]);
}

//Return value of *name
char	*minienv_value(char *name, t_env *minienv)
{
	t_env	*aux;

	aux = minienv_node(name, minienv);
	if (!aux)
		return (NULL);
	return (value_only(aux->key_pair));
}

//Adds *key_pair to **minienv
void	minienv_add(char *key_pair, t_env **minienv)
{
	t_env	*new_node;
	t_env	*aux_node;

	new_node = malloc(sizeof(t_env));
	new_node->key_pair = ft_strdup(key_pair);
	new_node->next = NULL;
	if (!*minienv)
	{
		*minienv = new_node;
		return ;
	}
	aux_node = *minienv;
	while (aux_node->next)
		aux_node = aux_node->next;
	aux_node->next = new_node;
}

//Creates *minienv
t_env	*init_minienv(char **environ)
{
	t_env	*minienv;
	char	*home;
	int		i;

	minienv = NULL;
	i = 0;
	while (environ[i])
		minienv_add(environ[i++], &minienv);
	if (!minienv_node("OLDPWD", minienv))
		minienv_add("OLDPWD", &minienv);
	home = ft_strjoin("__HOME=", minienv_value("HOME", minienv));
	minienv_add(home, &minienv);
	free(home);
	return (minienv);
}
