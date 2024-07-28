/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11exec_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:20:26 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/26 21:26:17 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_signal_interrupt(int status, int is_last_child)
{
	if (WTERMSIG(status) == SIGINT)
		ft_putstr_fd("\n", 1);
	if (WTERMSIG(status) == SIGQUIT && is_last_child)
		ft_putstr_fd("Quit\n", 1);
	return (INTERRUPT + WTERMSIG(status));
}

//WIFSIGNALED(status): Checks if the child process was terminated by a signal
//WIFEXITED(status): Checks if the child process terminated normally.
int	wait_for_child(int child_pid, int is_last_child)
{
	int	status;

	if (child_pid == FORK_ERROR)
		return (EXIT_FAILURE);
	if (waitpid(child_pid, &status, 0) == -1)
		print_perror_msg("waitpid", ft_itoa(child_pid));
	if (WIFSIGNALED(status))
		return (handle_signal_interrupt(status, is_last_child));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

void	define_heredoc_signals(int child_pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (child_pid == 0)
		sa_sigint.sa_handler = SIG_DFL;
	else
		sa_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

int	exec_heredoc(char *delimiter, int *exit_status, t_env *minienv, char *input)
{
	int	child_pid;

	child_pid = fork();
	define_heredoc_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork - exec_heredoc", delimiter);
	else if (child_pid == 0)
	{
		free(input);
		read_heredoc(exit_status, minienv, delimiter);
	}
	else
	{
		*exit_status = wait_for_child(child_pid, TRUE);
		signal_handler();
		if (*exit_status != EXIT_SUCCESS)
			return (FAILED);
	}
	return (SUCCESS);
}
