/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05free_minienv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:01:20 by ivotints          #+#    #+#             */
/*   Updated: 2024/09/17 19:12:10 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_perror_msg(char *command, char *perror_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	perror(perror_msg);
}

void	close_extra_fds(void)
{
	int	last_open_fd;

	last_open_fd = open("/tmp/last_fd", O_RDWR | O_CREAT, 0666);
	while (last_open_fd > 2)
		close(last_open_fd--);
}


void	close_all_fds(void)
{
	close_extra_fds();
	close(0);
	close(1);
	close(2);
}

void	free_minienv(t_env **minienv)
{
	t_env	*line;
	t_env	*next;

	line = *minienv;
	while (line)
	{
		free(line->key_pair);
		next = line->next;
		free(line);
		line = next;
	}
	minienv = NULL;
}
