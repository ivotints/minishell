/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:29:55 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:29:58 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	m_del_next_node(t_env **node)
{
	t_env	*temp;

	temp = (*node)->next;
	(*node)->next = ((*node)->next)->next;
	free(temp->key_pair);
	free(temp);
}

static void	remove_from_minienv(char *varname, t_env *m)
{
	while (m && m->next)
	{
		if (ft_strncmp((m->next)->key_pair, varname, ft_strlen(varname)) == 0)
		{
			if ((m->next)->key_pair[ft_strlen(varname)] == '=')
				return (m_del_next_node(&m));
		}
		m = m->next;
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
			remove_from_minienv(varname, *minienv);
		av++;
	}
	return (exit_status);
}
