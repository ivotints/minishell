/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:30:12 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/25 18:23:59 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **av, t_env *minienv)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (av[1] && av[2])
		return (print_error_msg("cd", "too many arguments"), EXIT_FAILURE);
	if (av[1] && !equal(av[1], "~"))
		path = av[1];
	else
		path = minienv_value("__HOME", minienv);
	if (path && chdir(path) != 0)
	{
		print_perror_msg("cd", av[1]);
		return (EXIT_FAILURE);
	}
	pwd = minienv_value("PWD", minienv);
	oldpwd = minienv_value("OLDPWD", minienv);
	if (oldpwd && pwd && *pwd)
		minienv_update("OLDPWD", pwd, minienv);
	if (pwd && *pwd)
		minienv_update("PWD", getcwd(cwd, PATH_MAX), minienv);
	return (EXIT_SUCCESS);
}
