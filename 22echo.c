/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:53:49 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/27 18:56:39 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **av)
{
	int	i;
	int	new_line;

	new_line = TRUE;
	i = 1;
	if (av[1] && ft_strncmp(av[1], "-n", 3) == 0)
	{
		new_line = FALSE;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
