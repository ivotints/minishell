/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30exec_fork_extern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:30:29 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:30:33 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parrent will ignore ctr+c ctr +\\, while child will have default
void	define_execute_signals(int child_pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (child_pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	exec_fork_extern(char **av, t_env *minienv)
{
	int		child_pid;
	char	*cmd;

	cmd = av[0];
	child_pid = fork();
	define_execute_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork", cmd);
	else if (child_pid == 0)
		execute_external(av, minienv);
	else
		return (wait_for_child(child_pid, TRUE));
	exit(EXIT_FAILURE);
}
