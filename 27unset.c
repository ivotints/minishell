/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:19:46 by ivotints          #+#    #+#             */
/*   Updated: 2024/09/25 13:23:38 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	m_del_node(t_env **node)
{
	t_env	*temp;

	temp = *node;
	*node = (*node)->next;
	free(temp->key_pair);
	free(temp);
}

static void	remove_from_minienv(char *varname, t_env **m)
{
	t_env	**prev_next;

	prev_next = m;
	while (*prev_next)
	{
		if (ft_strncmp((*prev_next)->key_pair, varname, ft_strlen(varname)) == 0
			&& (*prev_next)->key_pair[ft_strlen(varname)] == '=')
		{
			return (m_del_node(prev_next));
		}
		prev_next = &(*prev_next)->next;
	}
}

int	unset(char **av, t_env **minienv)
{
	char	*varname;
	int		exit_status;

	av++;
	exit_status = EXIT_SUCCESS;
	if (!*av)
		return (0);
	while (*av)
	{
		varname = *av;
		if (!is_valid_varname(varname))
		{
			print_varname_error_msg("unset", varname);
			exit_status = EXIT_FAILURE;
		}
		else
		{
			remove_from_minienv(varname, minienv);
		}
		av++;
	}
	return (exit_status);
}
