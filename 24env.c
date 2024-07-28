/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:06:02 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/27 20:15:15 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_env *minienv)
{
	while (minienv)
	{
		if (ft_strchr(minienv->key_pair, '='))
		{
			ft_putstr_fd(minienv->key_pair, 1);
			ft_putstr_fd("\n", 1);
		}
		minienv = minienv->next;
	}
	return (0);
}
