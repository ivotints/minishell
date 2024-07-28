/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:44:00 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/24 01:02:38 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	extern char	**environ;

	return (minishell(init_minienv(environ)));
}
