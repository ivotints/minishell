/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25builtin_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:16:15 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:16:54 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_varname_error_msg(char *command, char *varname)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(varname, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	is_valid_varname(char *name)
{
	if (!(ft_isalpha(*name) || *name == '_'))
		return (FALSE);
	while (*name)
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (FALSE);
		name++;
	}
	return (TRUE);
}

char	*name_only(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] && key_pair[i] != '=')
		i++;
	return (ft_substr(key_pair, 0, i));
}

static int	declare_env(t_env *minienv)
{
	char	*name;

	while (minienv)
	{
		ft_putstr_fd("declare -x ", 1);
		name = name_only(minienv->key_pair);
		ft_putstr_fd(name, 1);
		free(name);
		if (ft_strchr(minienv->key_pair, '='))
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(value_only(minienv->key_pair), 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		minienv = minienv->next;
	}
	return (0);
}

int	builtin_export(char **av, t_env **minienv)
{
	char	*key_pair;
	char	*varname;
	int		exit_status;

	av++;
	exit_status = EXIT_SUCCESS;
	if (!*av)
		return (declare_env(*minienv));
	while (*av)
	{
		key_pair = *av;
		varname = name_only(key_pair);
		if (!is_valid_varname(varname) || equal(key_pair, "="))
		{
			print_varname_error_msg("export", key_pair);
			exit_status = EXIT_FAILURE;
		}
		else if (minienv_node(varname, *minienv))
			minienv_update(varname, value_only(key_pair), *minienv);
		else
			minienv_add(key_pair, minienv);
		free(varname);
		av++;
	}
	return (exit_status);
}
