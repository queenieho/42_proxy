/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 22:30:02 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 22:43:44 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		ft_isnum(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int		ft_check_for_ip(char *str, char **ip)
{
	int		num;
	int		dots;
	int		i;

	i = 1;
	num = 0;
	dots = 0;
	if (ft_isnum(str[0]))
		num++;
	while (str[i])
	{
		if (str[i] == '.')
			dots++;
		if (ft_isnum(str[i]) && str[i - 1] == '.')
			num++;
		i++;
	}
	if (num == 4 && dots == 3)
	{
		*ip = strdup(str);
		return (0);
	}
	return (-1);
}

int		ft_get_info(char **av, t_connect *info)
{
	if ((ft_check_for_ip(av[1], &info->ip)) == -1)
		return (-1);
	else
	{
		info->port = strdup(av[2]);
	}
	return (0);
}
