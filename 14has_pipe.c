/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14has_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:26:14 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 21:28:29 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe(char *str)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (*str == '|')
			return (TRUE);
		str++;
	}
	return (FALSE);
}
