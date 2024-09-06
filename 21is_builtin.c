/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21is_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:28:11 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/06 11:22:28 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	equal(char *str1, char *str2)
{
	return (ft_strncmp(str1, str2, ft_strlen(str1) + 1) == 0);
}

int	execute_builtin(char **av, t_env **minienv)
{
	if (equal(*av, "echo"))
		return (echo(av));
	if (equal(*av, "pwd"))
		return (pwd());
	if (equal(*av, "env"))
		return (env(*minienv));
	if (equal(*av, "export"))
		return (builtin_export(av, minienv));
	if (equal(*av, "unset"))
		return (unset(av, minienv));
	if (equal(*av, "cd"))
		return (cd(av, *minienv));
	if (equal(*av, "exit"))
		return (builtin_exit(av, minienv));
	else
		return (EXIT_FAILURE);
}

int	is_builtin(char *cmd)
{
	if (equal(cmd, "echo"))
		return (TRUE);
	if (equal(cmd, "cd"))
		return (TRUE);
	if (equal(cmd, "pwd"))
		return (TRUE);
	if (equal(cmd, "export"))
		return (TRUE);
	if (equal(cmd, "unset"))
		return (TRUE);
	if (equal(cmd, "env"))
		return (TRUE);
	if (equal(cmd, "exit"))
		return (TRUE);
	return (FALSE);
}
