/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40wait_for_children.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:33:22 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:33:26 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_after_execute(int *children_pid)
{
	close_extra_fds();
	free(children_pid);
}

int	wait_for_children(int children_pid[1024])
{
	int	i;
	int	exit_status;
	int	is_last_child;

	i = 0;
	exit_status = 0;
	while (children_pid[i] != 0)
	{
		is_last_child = children_pid[i + 1] == 0;
		exit_status = wait_for_child(children_pid[i], is_last_child);
		i++;
	}
	clean_after_execute(children_pid);
	return (exit_status);
}
