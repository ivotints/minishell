/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17handle_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:53:59 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 21:11:36 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Everything that we write to second, writes to first.
void	redirect_fd(int fd_to_redirect, int fd_location)
{
	dup2(fd_to_redirect, fd_location);
	close(fd_to_redirect);
}

char	*get_redirect_position(char *str, char redirect_char)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (*str == redirect_char)
			return (str);
		str++;
	}
	return (str);
}

int	redirect_input(char *input)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;

	input_redirect = get_redirect_position(input, '<');
	if (!*input_redirect)
		return (SUCCESS);
	file_name = get_delimiter(input_redirect); //return us name of file
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("open2", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, 0); //now everything we read from STDIN (0) we read from a file
	free(file_name);
	return (SUCCESS);
}

void	save_original_fd_in(int original_fds[2])
{
	if (original_fds[0] == NO_REDIRECT)
		original_fds[0] = dup(0);
}

int	handle_input(char *input, int original_fds[2])
{
	save_original_fd_in(original_fds);
	if (redirect_input(input) == FAILED)
	{
		redirect_fd(original_fds[0], 0);
		return (FAILED);
	}
	return (SUCCESS);
}
