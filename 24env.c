/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludvik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:29:11 by rludvik           #+#    #+#             */
/*   Updated: 2024/09/05 17:29:13 by rludvik          ###   ########.fr       */
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
