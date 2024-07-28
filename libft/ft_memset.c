/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:55:45 by ivotints          #+#    #+#             */
/*   Updated: 2024/01/22 09:55:46 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n > 0)
	{
		str[n - 1] = c;
		n--;
	}
	return (s);
}

/* int	main(void)
{
	char c[] = "C programming can be very pleasant";
	char d[] = "C programming can be very pleasant";
	printf("%s\n", (char *)ft_memset(c, 256 + 48, 10));
	printf("%s\n",    (char *)memset(d, 256 + 49, 10));
} */
