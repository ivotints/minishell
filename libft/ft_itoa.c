/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:55:22 by ivotints          #+#    #+#             */
/*   Updated: 2024/01/28 18:16:39 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sizen(long long n)
{
	int	result;

	result = 0;
	if (n < 0)
	{
		n *= -1;
		result++;
	}
	while (n > 0)
	{
		result++;
		n = n / 10;
	}
	return (result);
}

static void	ft_convert(char *result, long long nb, int size)
{
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	if (!nb)
		result[0] = '0';
	result[size] = '\0';
	while (nb)
	{
		result[size - 1] = (nb % 10) + '0';
		nb = nb / 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	char		*result;
	int			size;
	long long	nb;
	char		*o;

	if (n == 0)
	{
		o = (char *)malloc(2);
		o[0] = '0';
		o[1] = 0;
		return (o);
	}
	nb = n;
	size = ft_sizen(nb);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_convert(result, nb, size);
	return (result);
}
