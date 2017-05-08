/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:40:00 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 22:13:55 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proxy.h"

int		ft_hostname_to_ip(char *hostname, char **ip)
{
	struct addrinfo		hints;
	struct addrinfo		*servinfo;
	struct addrinfo		*p;
	struct sockaddr_in	*h;
	int					rv;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if ((rv = getaddrinfo(hostname, NULL, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return (-1);
	}
	if (servinfo != NULL)
	{
		p = servinfo;
		while (p)
		{
			h = (struct sockaddr_in *)p->ai_addr;
			*ip = strdup(inet_ntoa(h->sin_addr));
			p = p->ai_next;
		}
	}
	return (0);
}

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

int		ft_get_info(int arg_count, char **av, t_connect *info)
{
	if ((ft_check_for_ip(av[1], &info->ip)) == -1)
		if ((ft_hostname_to_ip(av[1], &info->ip)) == -1)
			return (-1);
	if (!strcmp(info->ip, "0.0.0.0"))
	{
		printf("zero ip %s\n", info->ip);
		return (-1);
	}
	if (arg_count == 3)
	{
		info->s_port = strdup("22");
		info->c_port = strdup(av[2]);
	}
	else if (arg_count == 4)
	{
		info->s_port = strdup(av[2]);
		info->c_port = strdup(av[3]);
	}
	return (0);
}
