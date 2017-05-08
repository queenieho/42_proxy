/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:55:18 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 22:21:12 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_SIZE 65535

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;
	size_t			i;

	s2 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s2[i] = 0;
		i++;
	}
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*s1a;
	unsigned char	*s2a;

	i = 0;
	s1a = (unsigned char *)s1;
	s2a = (unsigned char *)s2;
	if (s1a[i] == '\0')
		return (s1a[i] - s2a[i]);
	while (s1a[i] != '\0' || s2a[i] != '\0')
	{
		if (s2a[i] == '\0')
			return (s1a[i]);
		else if (s2a[i] != s1a[i])
			return (s1a[i] - s2a[i]);
		i++;
	}
	return (0);
}

void	ft_reply(int comm_fd, char *str, int len)
{
	write(1, "Sending reply: ", 16);
	write(1, str, len);
	write(comm_fd, str, len);
}

void	ft_comm(int comm_fd)
{
	char	str[BUFF_SIZE];
	int		n;

	ft_bzero(str, BUFF_SIZE);
	if ((n = read(comm_fd, str, BUFF_SIZE - 1)) > 0)
	{
		write(1, "Incoming message: ", 19);
		write(1, str, n);
		if (ft_strcmp(str, "ping\n") == 0)
			ft_reply(comm_fd, "pong pong\n", 11);
		else
			ft_reply(comm_fd, str, n);
	}
}

int		main(int ac, char **av)
{
	int					socket_fd;
	int					comm_fd;
	struct sockaddr_in	s_addr;

	if (ac < 2)
	{
		write(2, "usage: ./server port_number\n", 29);
		exit(1);
	}
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	ft_bzero(&s_addr, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htons(INADDR_ANY);
	s_addr.sin_port = htons(atoi(av[1]));
	bind(socket_fd, (struct sockaddr *)&s_addr, sizeof(s_addr));
	listen(socket_fd, 5);
	comm_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL);
	while (1)
		ft_comm(comm_fd);
	return (0);
}
