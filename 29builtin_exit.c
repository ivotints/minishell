/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   29builtin_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:18:41 by ivotints          #+#    #+#             */
/*   Updated: 2024/07/28 17:25:49 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_error(char *command, char *msg, int error)
{
	print_error_msg(command, msg);
	close_all_fds();
	rl_clear_history();
	exit(error);
}

static int	fits_in_long_long(char *str)
{
	long long	out;
	int			c;
	char		*temp;

	str = trim_spaces_no_free(str);
	if (ft_strlen(str) > 20)
		return (free(str), FALSE);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (free(str), TRUE);
	temp = str;
	if (*str == '-' || *str == '+')
		str++;
	out = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (free(temp), FALSE);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (free(temp), FALSE);
		out = out * 10 + c;
		str++;
	}
	return (TRUE);
}

static long long	ft_atoll(const char *str)
{
	long long	number;
	int			sign;

	number = 0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (number * sign);
}

//av can be NULL if we sent ctrl+D
static void	check_av_error(char **av)
{
	if (!av || !av[1])
	{
		if (av)
			free_array(av);
		close_all_fds();
		exit(0);
	}
	if (!fits_in_long_long(av[1]))
	{
		free_array(av);
		exit_with_error("exit", "numeric argument required", BUILTIN_MISUSE);
	}
	if (av[2] != NULL)
	{
		free_array(av);
		exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
}

int	builtin_exit(char **av, t_env **minienv)
{
	int	exit_status;

	rl_clear_history();
	free_minienv(minienv);
	ft_putstr_fd("exit\n", 1);
	check_av_error(av);
	close_all_fds();
	exit_status = ft_atoll(av[1]);
	free_array(av);
	exit(exit_status);
}
