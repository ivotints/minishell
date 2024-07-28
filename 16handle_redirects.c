/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16handle_redirects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:59:59 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 20:08:16 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_original_fds(int original_fds[2])
{
	if (original_fds[0] != NO_REDIRECT)
		redirect_fd(original_fds[0], STDIN_FILENO);
	if (original_fds[1] != NO_REDIRECT)
		redirect_fd(original_fds[1], STDOUT_FILENO);
}

int	handle_redirects(char *input, int original_fds[2])
{
	char	redirect;

	original_fds[0] = NO_REDIRECT;
	original_fds[1] = NO_REDIRECT;
	redirect = *(get_rposition(input));
	while (redirect)
	{
		if (redirect == '<')
		{
			if (!handle_input(input, original_fds))
				return (FAILED);
		}
		if (redirect == '>')
		{
			if (!handle_output(input, original_fds))
				return (FAILED);
		}
		if (redirect == 1)
		{
			save_original_fd_in(original_fds);
			redirect_heredoc(input);
		}
		redirect = *get_rposition(input);
	}
	return (SUCCESS);
}
