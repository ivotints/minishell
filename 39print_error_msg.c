/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39print_error_msg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:33:11 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:33:14 by rludvik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(char *command, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
