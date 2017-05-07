/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 22:20:49 by qho               #+#    #+#             */
/*   Updated: 2017/05/07 13:38:53 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
// #include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define BUFF_SIZE 65535

typedef struct	s_connect
{
	char	*ip;	// if website is given, use gethostname to get ip.
	char	*s_port;	// port to connect to server, if not spec-ed, its 22
	char	*c_port;	// port for client to reach proxy
}				t_connect;

typedef struct	s_server
{
	int		client_fd;
	char	*ip;
	char	*port;
}				t_server;

int		ft_hostname_to_ip(char *hostname, char **ip)
{
	int		sockfd;
	struct	addrinfo		hints;
	struct	addrinfo		*servinfo;
	struct	addrinfo		*p;
	struct	sockaddr_in	*h;
	int		rv;

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

void	ft_socket_loop(t_server *info, int s_fd)
{
	char	buf[BUFF_SIZE];
	int		bytes;

	bytes = 0;
	while (1)
	{
		// get data from client
		memset(&buf, '\0', sizeof(buf));
		if ((bytes = read(info->client_fd, buf, sizeof(buf))) <= 0)
		{
			//client exits should return HOW TO CLOSE SOCKET?
			return ;
		}
		else
		{
			write(s_fd, buf, sizeof(buf));
			printf("From client:\n");
			fputs(buf, stdout);
			fflush(stdout);
		}
		// get data from server
		memset(&buf, '\0', sizeof(buf));
		if ((bytes = read(s_fd, buf, sizeof(buf))) <= 0)
		{
		}
		else
		{
			write(info->client_fd, buf, sizeof(buf));
			printf("From server:\n");
			fputs(buf, stdout);
			fflush(stdout);
		}
	}
}

void	*ft_run_socket(void *arg)
{
	t_server	*info;
	struct sockaddr_in	s_sd;
	int			s_fd;

	info = (t_server *)arg;
	s_fd = 0;
	// connect to main server
	if ((s_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("server socket not created\n");
	else
	{
		printf("server socket created\n");
		memset(&s_sd, 0, sizeof(s_sd));
		s_sd.sin_family = AF_INET;
		s_sd.sin_port = htons(atoi(info->port));
		s_sd.sin_addr.s_addr = inet_addr(info->ip);
		if((connect(s_fd, (struct sockaddr *)&s_sd, sizeof(s_sd))) < 0)
			printf("server connection not established\n");
		else
		{
			printf("server socket connected...\n");
			ft_socket_loop(info, s_fd);
		}
	}
	return (NULL);
}

void	ft_proxy_loop(int c_fd, int p_fd, char *ip, char *s_port)
{
	pthread_t tid;
	t_server *item;

	while (1)
	{
		c_fd = accept(p_fd, (struct sockaddr *)NULL, NULL);
		printf("client no. %d connected\n", c_fd);
		if (c_fd > 0)
		{
			item = (t_server *)malloc(sizeof(t_server));
			item->client_fd = c_fd;
			item->ip = strdup(ip);
			item->port = strdup(s_port);
			pthread_create(&tid, NULL, ft_run_socket, (void *)item);
			sleep(1);
		}
	}
}

void	ft_run_proxy(t_connect *info)
{
	int		c_fd;
	int		s_fd;
	struct	sockaddr_in c_sd;

	c_fd = 0;
	s_fd = 0;

	signal(SIGPIPE, SIG_IGN); // keeps proxy server running after client exits
	if ((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Failed to create socket\n");
	printf("Proxy created\n");
	memset(&c_sd, 0, sizeof(c_sd));
	c_sd.sin_family = AF_INET;
	c_sd.sin_port = htons(atoi(info->c_port));
	c_sd.sin_addr.s_addr = INADDR_ANY;
	if ((bind(c_fd, (struct sockaddr*)&c_sd, sizeof(c_sd))) < 0)
		printf("Failed to bind socket\n");
	if ((listen(c_fd, SOMAXCONN)) < 0)
		printf("Failed to listen\n");
	printf("Waiting for connection...\n"); // accept all client connections
	ft_proxy_loop(s_fd, c_fd, info->ip, info->s_port);
}

void	ft_clear_info(t_connect *info)
{
	free(info->ip);
	free(info->s_port);
	free(info->c_port);
}

int		main(int ac, char **av)
{
	t_connect	info;

	if (ac < 3 || ac > 4)
		printf("Invalid usage.\n");
	else
	{
		if ((ft_get_info(ac, av, &info)) == -1)
		{
			printf("Invalid hostname. Please confirm and try again\n");
			exit (1);
		}
		else
		{
			printf("ip :%s\n", info.ip);
			printf("s_port %s\n", info.s_port);
			printf("c_port %s\n", info.c_port);
			ft_run_proxy(&info);
			ft_clear_info(&info);
		}
	}
	return (0);
}
