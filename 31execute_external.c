/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31execute_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:11:12 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 20:18:03 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_execve_errors(char **args, char *path, char **envp)
{
	int	error;

	error = EXIT_FAILURE;
	print_perror_msg("execve", args[0]);
	if (access(path, F_OK) != 0)
		error = CMD_NOT_FOUND;
	else if (access(path, X_OK) != 0)
		error = NOT_EXECUTABLE;
	free_array(args);
	free_array(envp);
	free(path);
	exit(error);
}

static int	is_folder(char *command)
{
	struct stat	statbuf;

	if (stat(command, &statbuf) != 0)
		return (FALSE);
	if (S_ISDIR(statbuf.st_mode))
	{
		if (*command == '.')
			command++;
		if (*command == '.')
			command++;
		if (*command == '/')
			return (TRUE);
	}
	return (FALSE);
}

void	external_exit(char **av, t_env *minienv, int exit_status)
{
	if (exit_status == NOT_EXECUTABLE)
		print_error_msg(*av, NOT_EXECUTABLE_MSG);
	if (exit_status == CMD_NOT_FOUND)
		print_error_msg(*av, CMD_NOT_FOUND_MSG);
	rl_clear_history();
	free_minienv(&minienv);
	free_array(av);
	close_all_fds();
	exit(exit_status);
}

int	is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int	execute_external(char **av, t_env *minienv)
{
	char	*path;
	char	**envp;

	if (is_empty(*av))
		external_exit(av, minienv, CMD_NOT_FOUND);
	if (is_folder(*av))
		external_exit(av, minienv, NOT_EXECUTABLE);
	path = get_path(*av, minienv);
	if (path == NULL && (minienv_value("PATH", minienv) != NULL))
		external_exit(av, minienv, CMD_NOT_FOUND);
	else if (path == NULL)
		path = ft_strdup(*av);
	rl_clear_history();
	close_extra_fds();
	envp = minienv_to_envp(minienv);
	free_minienv(&minienv);
	if (execve(path, av, envp) == -1)
		handle_execve_errors(av, path, envp);
	exit(EXIT_SUCCESS);
}
