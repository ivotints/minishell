/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19redirect_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:01:22 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/27 16:02:41 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_heredoc(char *command)
{
	int		tmp_file_fd;

	tmp_file_fd = open("/tmp/minishell_hd", O_RDONLY);
	if (tmp_file_fd == -1)
	{
		print_perror_msg("open", "/tmp/minishell_hd");
		return ;
	}
	redirect_fd(tmp_file_fd, 0); // now we read not from 0 but from temp file
	delete_char(get_redirect_position(command, 1), 1);
}
