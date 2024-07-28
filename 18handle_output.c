/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18handle_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:55:32 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 21:11:43 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(char *command)
{
	char	*output_redirect;
	char	*file_name;
	int		fd;
	int		open_flags;

	output_redirect = get_redirect_position(command, '>');
	if (!*output_redirect)
		return (SUCCESS);
	if (output_redirect[1] == '>')
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	file_name = get_delimiter(output_redirect);
	fd = open(file_name, open_flags, 0644);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, 1); //now everything we write to STDOUT (1) we write to a file
	free(file_name);
	return (SUCCESS);
}

void	save_original_fd_out(int original_fds[2])
{
	if (original_fds[1] == NO_REDIRECT)
		original_fds[1] = dup(1);
}

int	handle_output(char *command, int original_fds[2])
{
	save_original_fd_out(original_fds);
	if (redirect_output(command) == FAILED)
	{
		redirect_fd(original_fds[1], 1);
		return (FAILED);
	}
	return (SUCCESS);
}
